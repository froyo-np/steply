module;
#include <string>
#define max(a,b) a > b ? a : b
#define abs(a) a >= 0 ? a : -a
#include "guiDef.h"
#define sName "empty"
#define sDef ""
#define fnName "sdfIntersect"
#define fnDef R"(float sdfIntersect(float a,float b)
			{
				return max(a,b);
			})"

#define ssName "float"
#define ssDef ""
#define sfnName "sdfSmoothIntersect"
#define sfnDef R"(float sdfSmoothIntersect(float radius, float a, float b)
			{
				float h = max(radius - abs(a - b), 0.0);
				return max(a, b) + h * (h *0.25 / radius);
			})"
export module sdfIntersect;
import imvec;
import string_helpers;

export namespace SDF {
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
		decl_uiName(intersect, "intersect");
		decl_uiName(smoothIntersect, "smooth intersect");
		
		decl_glslInterface(intersect,sName, sDef,fnName,fnDef)
		decl_glslInterface(smoothIntersect, ssName, ssDef, sfnName, sfnDef)
		export template <typename F>
		std::string glslLiteral(const intersect<F>& self) {
			return std::string("");
		}
		export template <typename F>
		std::string glslLiteral(const smoothIntersect<F>& self) {
			return print(self.radius);
		}
}