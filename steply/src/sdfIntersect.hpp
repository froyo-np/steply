#pragma once
#include <string>
#include "guiDef.h"

#include "imvec\imvec.hpp"
#include "string_helpers.h"

namespace SDF {
		template <typename F>
		struct intersect {
			// intentionally empty!
		};
		template <typename F>
		inline F sdfBinaryOp(const intersect<F>& i, F a, F b) {
			return max(a, b);
		}
		template <typename F>
		struct smoothIntersect {
			F radius;
			smoothIntersect() : radius(0.0) {}
			smoothIntersect(F r) : radius(r) {}

		};
		template <typename F>
		inline F sdfBinaryOp(const smoothIntersect<F>& i, F d1, F d2) {
			F k = i.radius;
			F h = max(k - abs(d1 - d2), 0.0);
			return max(d1, d2) + h * (h * 0.25 / k);
		}
		decl_uiName(intersect, "intersect")
		decl_uiName(smoothIntersect, "smooth intersect")
		
		decl_glslInterface(intersect,"empty", "","sdfIntersect",
			R"(float sdfIntersect(float a,float b)
			{
				return max(a,b);
			})")
		decl_glslInterface(smoothIntersect, "float", "", "sdfSmoothIntersect",
			R"(float sdfSmoothIntersect(float radius, float a, float b)
			{
				float h = max(radius - abs(a - b), 0.0);
				return max(a, b) + h * (h *0.25 / radius);
			})")
		template <typename F>
		std::string glslLiteral(const intersect<F>& self) {
			return std::string("");
		}
		template <typename F>
		std::string glslLiteral(const smoothIntersect<F>& self) {
			return print(self.radius);
		}
}