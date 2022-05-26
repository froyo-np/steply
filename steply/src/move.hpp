#pragma once
#define UI_NAME "offset"
#include "guiDef.h"
#include <string>

#include "imvec\imvec.hpp"
#include "string_helpers.h"

namespace SDF {

	template <typename F>
	struct move {
		imvec::vec<F, 3> offset;
	};

	template <typename F>
	inline imvec::vec<F, 3> sdfDomainOp(const move<F>& trn, const imvec::vec<F, 3>& pnt) {
		return trn.offset + pnt;
	}
	decl_uiName(move, "offset")
	decl_glslInterface(move, 
		"vec3",
		"",
		"sdfTranslate",
		R"(vec3 sdfTranslate(vec3 trn, vec3 p)
		{
			return p + trn;
		})")
	template <typename F>
	std::string glslLiteral(const move<F>& self) {
		return vecLiteral<F, 3>(self.offset);
	}
};
