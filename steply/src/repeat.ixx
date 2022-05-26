module;
#define UI_NAME "repeat"
#include "guiDef.h"
#include <string>
#define sName "repeat"
#define sDef "struct repeat {vec3 reps; vec3 stepSize;};"
#define fnName "sdfRepeat"
#define fnDef "vec3 " fnName R"((repeat self, vec3 p)
			{
				vec3 c = self.stepSize;
				vec3 l = self.reps;
				vec3 k = p-c*clamp(round(p/c),-l,l);
				// but use the normal one... if we're out of bounds?
				return k;
			})"
export module repeat;
import imvec;
import string_helpers;

export namespace SDF {
	using namespace ivec;
	template <typename F>
	struct repeat {
		vec<F, 3> reps;
		vec<F, 3> stepSize;
		repeat(const vec<F, 3>& counts, const vec<F, 3>& sizes) : reps(counts), stepSize(sizes) {}
		repeat() : reps(vec<F, 3>(3, 1, 3)), stepSize(vec<F, 3>(100, 100, 100)) {}
	};

	template <typename F>
	inline vec<F, 3> sdfDomainOp(const repeat<F>& t, const ivec::vec<F, 3>& p) {
		using vec3 = vec<F, 3>;
		vec3 c = t.stepSize;
		vec3 l = t.reps;
		vec3 k = p - c * vec3::Min(vec3::Max((p / c).round(), l * -1.0), l);
		return k;
	}
	decl_uiName(repeat, UI_NAME)
	decl_glslInterface(repeat, sName, sDef, fnName, fnDef)
	template <typename F>
	std::string glslLiteral(const repeat<F>& self) {
		return std::string(sName) + "(" + vecLiteral<F,3>(self.reps) + ", " + vecLiteral<F, 3>(self.stepSize) + ")";
	}
};

