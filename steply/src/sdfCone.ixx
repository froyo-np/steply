module;
#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b
#define UI_NAME "cone"
#include "guiDef.h"
#include <string>
#define sName "cone"
#define sDef "struct " sName "{float radius; float height;};"
#define fnName "sdfCone"

#define fnBody R"(
  float h = self.height;
  vec2 q = vec2(self.radius, -h);
    
  vec2 w = vec2( length(p.xz), p.y );
  vec2 a = w - q*clamp( dot(w,q)/dot(q,q), 0.0, 1.0 );
  vec2 b = w - q*vec2( clamp( w.x/q.x, 0.0, 1.0 ), 1.0 );
  float k = sign( q.y );
  float d = min(dot( a, a ),dot(b, b));
  float s = max( k*(w.x*q.y-w.y*q.x),k*(w.y-q.y)  );
  return sqrt(d)*sign(s);
)"
#define fnDef decl_glslFunc(fnName,sName,fnBody)

export module sdfCone;
import string_helpers;
import imvec;
export namespace SDF {
	using namespace ivec;
		template <typename F>
		struct cone {
			F radius;
			F height;
			cone() : radius(0.5), height(1.0) { }
			cone(F r, F h) : radius(r), height(h) {}
			/*Box3 getBound() const {
				return Box3(Vec3(-radius, 0, -radius), Vec3(radius, height, radius));
			}*/
		};
		template <typename F>
		F distanceTo(const cone<F>& self, const vec<F, 3>& p) {
			vec<F, 3> a = vec<F, 3>(0, -self.height, 0);
			vec<F, 3> b = vec<F, 3>(0, 0, 0);
			vec<F, 3> ab = b;
			vec<F, 3> pa = p;

			F t = max(0, min(1, pa.dot(ab) / ab.dot(ab)));
			F effectiveR = (1.0 - t) * self.radius;
			F d = (((ab * t) + a) - p).length() - effectiveR;
			if (t > 0.0) {
				return d;
			}
			// project p onto a point on the disc of the bottom of the cone...
			vec<F, 3> r(p.x(), 0, p.z());
			F pt = p.scalarProjectOnto(r);
			auto wtf = r.direction();
			auto j = min(self.radius, max(0, pt));
			vec<F, 3> ptr = wtf * j;
			return (p - ptr).length();
		}
		decl_uiName(cone, UI_NAME);
		decl_glslInterface(cone, sName,sDef,fnName,fnDef)
		export template <typename F>
		std::string glslLiteral(const cone<F>& self) {
			return std::string(sName) + "(" + print(self.radius)+", "+print(self.height) + ")";
		}
		
}