module;
#define UI_NAME "sphere"
#include "guiDef.h"
#include <string>

#define sName "float"
#define sDef ""
#define fnName "sdfSphere"
#define fnDef R"(float sdfSphere(float radius, vec3 p)
			{
				return length(p) - radius;
			})"
export module sdfSphere;
import imvec;
import string_helpers;
export namespace SDF {
	using namespace ivec;
		template <typename F>
		struct sphere {
			F radius;
			sphere() : radius(1.0) {}
			sphere(F r) : radius(r) {}
		};
		template <typename F>
		inline F distanceTo(const sphere<F>& self, const vec<F, 3>& p) {
			return p.length() - self.radius;
		}
		decl_uiName(sphere, UI_NAME);
		decl_glslInterface(sphere,sName,sDef,fnName,fnDef)
		export template <typename F>
		std::string glslLiteral(const sphere<F>& self) {
			return print(self.radius);
		}
};