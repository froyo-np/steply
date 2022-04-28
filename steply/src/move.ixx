module;
#define UI_NAME "offset"
#include "guiDef.h"
#include <string>
#define sName "vec3"
#define sDef ""
#define fnName "sdfTranslate"
#define fnDef R"(vec3 sdfTranslate(vec3 trn, vec3 p)
			{
				return p + trn;
			})"
export module move;
import imvec;
import string_helpers;

export namespace SDF {

	template <typename F>
	struct move {
		ivec::vec<F, 3> offset;
	};

	template <typename F>
	inline ivec::vec<F, 3> sdfDomainOp(const move<F>& trn, const ivec::vec<F, 3>& pnt) {
		return trn.offset + pnt;
	}
	decl_uiName(move, UI_NAME);
	decl_glslInterface(move,sName,sDef,fnName,fnDef)
	export template <typename F>
	std::string glslLiteral(const move<F>& self) {
		return vecLiteral<F, 3>(self.offset);
	}
};
