module;
#define UI_NAME "torus"
#include "guiDef.h"
#include <string>
#define sName "torus"
#define sDef "struct torus {float radius; float thickness;};"
#define fnName "sdfTorus"
#define fnDef R"(float sdfTorus(torus self, vec3 p)
			{
				float x = length(p.xz) - self.radius;
				vec2 s = vec2(x,p.y);
				return length(s) - self.thickness;
			})"


export module sdfTorus;

import imvec;
import string_helpers;
export namespace SDF {
	using namespace ivec;
		template <typename F>
		struct torus {
			F radius;
			F thickness;
			torus() : radius(0.5), thickness(1.0) { }
			torus(F r, F t) : radius(r), thickness(t) {}
			
		};
		template <typename F>
		F distanceTo(const torus<F>& self, const vec<F, 3>& p) {
			F x = p.xz().length() - self.radius;
			vec<F, 2> s(x, p.y());
			return s.length() - self.thickness;
		}
		decl_uiName(torus, UI_NAME);
		decl_glslInterface(torus, sName, sDef, fnName, fnDef)
		export template <typename F>
		std::string glslLiteral(const torus<F>& self) {
			return std::string(sName) + "(" + print(self.radius) + ", " + print(self.thickness) + ")";
		}
};