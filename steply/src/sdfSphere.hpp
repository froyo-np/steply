#pragma once
#include "guiDef.h"
#include <string>

#include "imvec\imvec.hpp"
#include "string_helpers.h"
namespace SDF {
	using namespace imvec;
		template <typename F>
		struct sphere {
			F radius;
			sphere() : radius(1.0) {}
			sphere(F r) : radius(r) {}
		};
		template <typename F>
		inline F distanceTo(const sphere<F>& self, const vec<F, 3>& p) {
			return p.length() - self.radius;
		}
		decl_uiName(sphere, "sphere")
		decl_glslInterface(sphere,"sphere","","sdfSphere", 
			R"(float sdfSphere(float radius, vec3 p)
			{
				return length(p) - radius;
			})")
		template <typename F>
		std::string glslLiteral(const sphere<F>& self) {
			return print(self.radius);
		}
};