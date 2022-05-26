#include "previewShader.h"



// return a function like: marchResult march(vec3 start, vec3 dir, float thresh);
std::string codegen::buildObjRayMarchFn() {
	// its fully static, since we wrapped the fn directly!
	return std::string(marchFn);
}

// return a function like: vec3 evalNormal(vec3 p, float e)
std::string codegen::buildNormalEstimation() {
	return std::string(evalNormalFn);
}

std::string codegen::getBasicVsrc() {
	return std::string(vsrcBody);
}
