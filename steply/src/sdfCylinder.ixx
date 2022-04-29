module;
#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b
#define UI_NAME "cylinder"
#include "guiDef.h"
#include <string>
#define sName "cylinder"
#define sDef "struct " sName "{ float radius; float height;};"
#define fnName "sdfCylinder"
#define fnBody R"(
				float d = length(p.xz) - self.radius;
				return max(d, abs(p).y - self.height);
			)"
#define fnDef decl_glslFunc(fnName, sName, fnBody)

export module sdfCylinder;
import string_helpers;
import imvec;
export namespace SDF {
	using namespace ivec;
	template <typename F>
	struct cylinder {
		F radius;
		F height;
		cylinder() : radius(0.5), height(1.0) { }
		cylinder(F r, F h) : radius(r), height(h) {}
		
	};
	template <typename F>
	F distanceTo(const cylinder<F>& self, const vec<F, 3>& p) {
		F d = p.xz().length() - self.radius;
		return max(d, p.abs().y() - self.height);
	}
	decl_uiName(cylinder, UI_NAME);
	decl_glslInterface(cylinder, sName, sDef, fnName, fnDef)
	export template <typename F>
	std::string glslLiteral(const cylinder<F>& self) {
		return std::string(sName) + "(" + print(self.radius) + ", " + print(self.height) + ")";
	}
}