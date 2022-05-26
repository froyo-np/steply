#pragma once

#include "guiDef.h"
#include <string>

#include "string_helpers.h"
#include "imvec\imvec.hpp"
namespace SDF {
	using namespace imvec;
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
	decl_uiName(cylinder, "cylinder")
	decl_glslInterface(cylinder, "cylinder", "struct cylinder{ float radius; float height;};", "sdfCylinder", 
		decl_glslFunc("sdfCylinder", "cylinder", R"(
				float d = length(p.xz) - self.radius;
				return max(d, abs(p).y - self.height);
			)")
	)
	template <typename F>
	std::string glslLiteral(const cylinder<F>& self) {
		return std::string("cylinder") + "(" + print(self.radius) + ", " + print(self.height) + ")";
	}
}