module;
#define max(a,b) a > b ? a : b
#define min(a,b) a < b ? a : b
#define abs(v) v >= 0 ? v : -v
#include "guiDef.h"
#include <string>
#define sName "empty"
#define sDef ""
#define fnName "sdfSubtract"
#define fnDef R"(float sdfSubtract(float a,float b)
			{
				return max(a,-b);
			})"
#define ssName "float"
#define ssDef ""
#define sfnName "sdfSmoothSubtract"
#define sfnDef R"(float sdfSmoothSubtract(float radius, float a, float b)
			{
				float h = max(radius - abs(-b - a), 0.0);
				return max(-b, a) + h * (h *0.25 / radius);
			})"
export module sdfSubtract;
import imvec;
import string_helpers;
export namespace SDF {
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
	decl_uiName(subtract, "subtract");
	decl_uiName(smoothSubtract, "smooth subtract");

	decl_glslInterface(subtract, sName, sDef, fnName, fnDef);
	decl_glslInterface(smoothSubtract,ssName,ssDef,sfnName,sfnDef)
	export template <typename F>
		std::string glslLiteral(const subtract<F>& self) {
		return std::string("");
	}
	export template <typename F>
		std::string glslLiteral(const smoothSubtract<F>& self) {
		return print(self.radius);
	}
}