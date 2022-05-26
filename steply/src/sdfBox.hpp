#pragma once
// we use macros in .ixx modules to privately conjoin some compile-time strings
// its fun!
#include "guiDef.h"
#include <string>
#include "imvec/imvec.hpp"
#include "string_helpers.h"
namespace SDF {
		using namespace imvec;
		template <typename F>
		struct box {
			imvec::vec<F, 3> dim;
			box() : dim(vec<F, 3>(1, 1, 1)) {}
			box(vec<F, 3> size) : dim(size) {}
			
		};
		template <typename F>
		F distanceTo(const box<F>& self, const vec<F, 3>& p) {
			vec<F, 3> d = p.abs() - self.dim;
			vec<F, 3> z(0, 0, 0);
			return d.Max(z).length() + d.Min(z).maxComponent();
		}
		decl_uiName(box, "box")
		decl_glslInterface(box, "box", "struct box {vec3 dim;};","sdfBox", 
			decl_glslFunc("sdfBox","box", 
				R"(
				vec3 d = abs(p)-self.dim;
				vec3 z = vec3(0,0,0);
				vec3 m = min(d,z);
				return length(max(d,z)) + max(m.x,max(m.y,m.z));)")
		)

		template <typename F>
			std::string glslLiteral(const box<F>& self) {
			return std::string("box") + "(" + vecLiteral<F, 3>(self.dim) + ")";
		}
};
