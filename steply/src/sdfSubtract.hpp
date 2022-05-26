#pragma once
#include <string>
#include "guiDef.h"

#include "imvec\imvec.hpp"
#include "string_helpers.h"
namespace SDF {
	template <typename F>
	struct subtract {
		// intentionally empty!
	};
	template <typename F>
	inline F sdfBinaryOp(const subtract<F>& i, F a, F b) {
		return max(a, -b);
	}
	template <typename F>
	struct smoothSubtract {
		F radius;
		smoothSubtract() : radius(0.0) {}
		smoothSubtract(F r) : radius(r) {}

	};
	template <typename F>
	inline F sdfBinaryOp(const smoothSubtract<F>& i, F a, F b) {
		F k = i.radius;
		F h = max(k - abs(-b - a), 0.0);
		return max(-b, a) + h * h * 0.25 / k;
	}
	decl_uiName(subtract, "subtract")
	decl_uiName(smoothSubtract, "smooth subtract")

	decl_glslInterface(subtract, "empty", "", "sdfSubtract",
		R"(float sdfSubtract(float a,float b)
		{
			return max(a,-b);
		})")
	decl_glslInterface(smoothSubtract,"float","","sdfSmoothSubtract",
		R"(float sdfSmoothSubtract(float radius, float a, float b)
		{
			float h = max(radius - abs(-b - a), 0.0);
			return max(-b, a) + h * (h *0.25 / radius);
		})")
	template <typename F>
		std::string glslLiteral(const subtract<F>& self) {
		return std::string("");
	}
	template <typename F>
		std::string glslLiteral(const smoothSubtract<F>& self) {
		return print(self.radius);
	}
}