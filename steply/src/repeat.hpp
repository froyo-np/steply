#pragma once
#include "guiDef.h"
#include <string>

#include "imvec\imvec.hpp"
#include "string_helpers.h"
constexpr auto sname = "repeat";
namespace SDF {
	using namespace imvec;
	template <typename F>
	struct repeat {
		vec<F, 3> reps;
		vec<F, 3> stepSize;
		repeat(const vec<F, 3>& counts, const vec<F, 3>& sizes) : reps(counts), stepSize(sizes) {}
		repeat() : reps(vec<F, 3>(3, 1, 3)), stepSize(vec<F, 3>(100, 100, 100)) {}
	};

	template <typename F>
	inline vec<F, 3> sdfDomainOp(const repeat<F>& t, const imvec::vec<F, 3>& p) {
		using vec3 = vec<F, 3>;
		vec3 c = t.stepSize;
		vec3 l = t.reps;
		vec3 k = p - c * vec3::Min(vec3::Max((p / c).round(), l * -1.0), l);
		return k;
	}
	decl_uiName(repeat, "repeat")
	decl_glslInterface(repeat, "repeat",
		"struct repeat {vec3 reps; vec3 stepSize;};",
		"sdfRepeat",
		"vec3 sdfRepeat " R"((repeat self, vec3 p)
			{
				vec3 c = self.stepSize;
				vec3 l = self.reps;
				vec3 k = p-c*clamp(round(p/c),-l,l);
				// but use the normal one... if we're out of bounds?
				return k;
			})")
	template <typename F>
	std::string glslLiteral(const repeat<F>& self) {
		return std::string("repeat") + "(" + vecLiteral<F,3>(self.reps) + ", " + vecLiteral<F, 3>(self.stepSize) + ")";
	}
};

