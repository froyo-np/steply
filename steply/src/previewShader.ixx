module;
#include <string>
#define dstFnSig R"(float evalDistance(vec3 pnt)
)"
#define marchResultStructDecl R"(struct marchResult {float dst;vec3 point;};
)"
#define marchFnSig R"(marchResult march(vec3 start, vec3 dir, float thresh))"
#define marchFnBody R"(
{
	float dst = 0.0;
	vec3 pnt = start;
	for (int i = 0; i < 228; ++i) {
		dst = evalDistance(pnt);
		if(dst < thresh){
			break;
		}
		pnt += (dir*max(thresh*5.0,dst));
	} // end march loop
	return marchResult(dst, pnt);
}
)"
#define marchFn marchResultStructDecl marchFnSig marchFnBody

// now a function to estimate the normal vector at any point
#define evalNormalSig R"(vec3 evalNormal(vec3 p, float e))"
// tetrahedron method - shameless theft / thanks iquilezles!
#define evalNormalBody R"(
{
	// figure out dDst/{dx,dy,dz} aka the gradient of the distance fn
    const vec2 k = vec2(1,-1);
    return normalize( k.xyy*evalDistance( p + k.xyy*e ) + 
                      k.yyx*evalDistance( p + k.yyx*e ) + 
                      k.yxy*evalDistance( p + k.yxy*e ) + 
                      k.xxx*evalDistance( p + k.xxx*e ) );
}
)"
#define evalNormalFn evalNormalSig evalNormalBody

constexpr const char* directRenderFragmentShader = R"(
uniform mat4 mdl;
varying vec3 origin;
varying vec3 p;
const float kDistThresh = 0.0003;
const vec3 lColor = vec3(0.75,0.75,0.75);
const vec3 lightPos = vec3(32,12,-2);
const vec3 ambLight = vec3(0.32,0.32,0.32);
const vec3 offLightPos = vec3(-30,-12,-12);
float shadowRamp(float lDst, float lmDst){
	float d = lDst - lmDst;
	float k = 1.0-smoothstep(kDistThresh*0.5,kDistThresh*15.0,d*d);
	return clamp(k+0.2, 0.0, 1.0);
}
vec3 applyLighting(marchResult result, vec3 nrml){
	
	vec4 lp1 = mdl*vec4(lightPos,1.0);
	vec4 lp2 = mdl*vec4(offLightPos,1.0);
	
	float dstFromLight = length(result.point-lp1.xyz);
	vec3 lDir = normalize(result.point-lp1.xyz);

	marchResult shadowRay = march(lp1.xyz, lDir, kDistThresh);
	float measuredLDist = length(shadowRay.point-lp1.xyz);
	float shadowFactor = shadowRamp(dstFromLight,measuredLDist);
	shadowFactor*=shadowFactor;
	
	
	float pLightCmp = clamp(dot(nrml, -normalize(lDir)),0.0,1.0);
	float offLightCmp = clamp(dot(nrml, normalize(lp2.xyz)),0.0,1.0)/3.0;
	
	vec3 lightCmp = clamp(ambLight + (ambLight*offLightCmp) + pLightCmp*lColor*shadowFactor,0.0,1.0);
	return lightCmp;
}
void main(){
	vec3 pnt = p; //(mdl*vec4(p,1.0)).xyz;
	float alpha = 0.0;
	vec3 dir = normalize(pnt-origin);
	marchResult result = march(pnt, dir, kDistThresh);
	vec3 nrml = vec3(1,0,0);
	vec3 lCmp = vec3(0,0,0);
	if((result.dst) <= kDistThresh){
		// todo: pick epsilon based on dst from camera
		nrml = evalNormal(result.point, kDistThresh);
		lCmp = applyLighting(result, nrml);
		alpha = 1.0;
	}
	vec3 surfaceColor = vec3(0.75)+(nrml)/4.0;
	// TODO write to frag_crd.z to set the depth correctly!
	gl_FragData[0] = vec4(surfaceColor*lCmp, alpha);

}
)";


constexpr const char* vsrcBody =
R"(
uniform vec3 o;
uniform float z;
uniform mat4 mdl;

attribute vec2 vPos;
attribute vec2 cPos;

varying vec3 origin;
varying vec3 p;

void main(){
	// o is camera origin
	// z is the dist to the near-clip plane, which lets us figure out
	// the frustrum...
	
	origin = (mdl*vec4(o,1.0)).xyz;
	p = (mdl*vec4(vPos.x,vPos.y,z,1.0)).xyz;
	gl_Position = vec4(2.0*(cPos-0.5), 0.0, 1.0);
}
)";

export module previewShader;
import DynamicShader;
import glslVisitor;
import imvec;

export namespace codegen {
	using namespace SDF;
	template <typename F, typename GroupType>
	std::string buildObjEvaluationCall(const typename GroupType::NodeVariant& obj) {
		glslDirectCallVisitor<F, GroupType> callme(std::string("pnt"));
		callme.visit(obj);
		return callme.getExpr();
	}
	// return a function like: float evalDistance(vec3 pnt)
	template <typename F, typename GroupType>
	std::string buildObjEvaluationFn(const typename GroupType::NodeVariant& obj) {
		auto expr = buildObjEvaluationCall<F, GroupType>(obj);
		return std::string(dstFnSig) + "{\n\t return " + expr + ";\n}\n";
	}
	// return a function like: marchResult march(vec3 start, vec3 dir, float thresh);
	std::string buildObjRayMarchFn() {
		// its fully static, since we wrapped the fn directly!
		return std::string(marchFn);
	}
	// return a function like: vec3 evalNormal(vec3 p, float e)
	std::string buildNormalEstimation() {
		return std::string(evalNormalFn);
	}
	std::string getBasicVsrc() {
		return std::string(vsrcBody);
	}
	template <typename F, typename GroupType>
	std::string buildDirectRenderShader(const typename GroupType::NodeVariant& obj) {
		glslHeaderVisitor<F, GroupType> headers;
		headers.visit(obj);
		std::string header("#version 130\n");
		for (auto sdef : headers.structDefs) {
			header += sdef.second + "\n";
		}
		for (auto fndef : headers.fnDefs) {
			header += fndef.second + "\n";
		}
		// now add evalDistance, evalNormal, march
		header += buildObjEvaluationFn<F, GroupType>(obj) + "\n";
		header += buildObjRayMarchFn() + "\n";
		header += buildNormalEstimation() + "\n";

		// this shader will render the object directly, under some simple lighting conditions
		// maybe add ambient occlusion estimation and shadows someday
		return header + std::string(directRenderFragmentShader);
	}
};
