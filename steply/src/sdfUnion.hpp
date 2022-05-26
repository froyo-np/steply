#pragma once
#include <string>
#include "guiDef.h"

#include "imvec\imvec.hpp"
#include "string_helpers.h"
namespace SDF {
	// 'union' is of course a keyword - blerg
	template <typename F>
	struct union_sdf {
		// intentionally empty!
	};
	template <typename F>
	inline F sdfBinaryOp(const union_sdf<F>& i, F a, F b) {
		return min(a, b);
	}
	template <typename F>
	struct smoothUnion {
		F radius;
		smoothUnion() : radius(0.0) {}
		smoothUnion(F r) : radius(r) {}

	};
	template <typename F>
	inline F sdfBinaryOp(const smoothUnion<F>& i, F a, F b) {
		F r = i.radius;
		imvec::vec<F, 2> u = imvec::vec<F, 2>(max(0, r - a), max(0, r - b));
		return max(r, min(a, b)) - u.length();
	}
	decl_uiName(union_sdf, "union")
	decl_uiName(smoothUnion, "smooth union")
	decl_glslInterface(union_sdf, "empty", "", "sdfUnion", "float sdfUnion(float a, float b) { return min(a, b); }")
	decl_glslInterface(smoothUnion, "float", "", "sdfRoundUnion",
		R"(float sdfRoundUnion(float radius, float a, float b){
			vec2 u = vec2(max(0.0, radius -a), max(0.0, radius - b));
			return max(radius, min(a,b))-length(u);
		})")
	
	template <typename F>
	std::string glslLiteral(const union_sdf<F>& self) {
		return std::string("");
	}
	template <typename F>
	std::string glslLiteral(const smoothUnion<F>& self) {
		return print(self.radius);
	}
}