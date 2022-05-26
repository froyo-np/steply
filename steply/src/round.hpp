#pragma once
#include "guiDef.h"
#include <string>
#include "string_helpers.h"

namespace SDF {
	template <typename F>
	struct round {
		F radius;
	};
	template <typename F>
	inline F sdfUnaryOp(const round<F>& i, F a) {
		return a - i.radius;
	}
	decl_uiName(round, "round")
	decl_glslInterface(round,
		"round",
		"",
		"sdfRound",
		R"( float sdfRound(float self, float dst)
		{
			return dst - self;
		})")
	template <typename F>
	std::string glslLiteral(const round<F>& self) {
		return print(self.radius);
	}
}