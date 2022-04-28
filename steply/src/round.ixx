module;
#define UI_NAME "round"
#include "guiDef.h"
#include <string>
#define sName "float"
#define sDef ""
#define fnName "sdfRound"
#define fnDef "float " fnName "(" sName R"( self, float dst)
			{
				return dst - self;
			})"
export module round;
import string_helpers;

export namespace SDF {
	template <typename F>
	struct round {
		F radius;
	};
	template <typename F>
	inline F sdfUnaryOp(const round<F>& i, F a) {
		return a - i.radius;
	}
	decl_uiName(round, UI_NAME);
	decl_glslInterface(round,sName,sDef,fnName,fnDef)
	export template <typename F>
	std::string glslLiteral(const round<F>& self) {
		return print(self.radius);
	}
}