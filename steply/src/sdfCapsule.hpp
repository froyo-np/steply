#pragma once
#include "guiDef.h"
#include <string>

#include "string_helpers.h"
#include "imvec\imvec.hpp"
namespace SDF {
	using namespace imvec;
	template <typename F>
	struct capsule {
		vec<F, 3> a;
		vec<F, 3> b;
		F radius;
		capsule() : a(vec<F, 3>(0, 0, 0)), b(vec<F, 3>(0, 1, 0)), radius(0.5) {}
		capsule(vec<F, 3> A, vec<F, 3> B, F r) : radius(r), a(A), b(B) {}
		
	};
	template <typename F>
	F distanceTo(const capsule<F>& self, const vec<F, 3>& p) {
		vec<F, 3> ab = self.b - self.a;
		vec<F, 3> pa = p - self.a;
		F t = max(0, min(1, pa.dot(ab) / ab.dot(ab)));
		return (((ab * t) + self.a) - p).length() - self.radius;
	}
	decl_uiName(capsule, "capsule")
	decl_glslInterface(capsule, "capsule", "struct capsule {vec3 a; vec3 b;float radius;};", "sdfCapsule",
		decl_glslFunc("sdfCapsule","capsule", 
			R"(
			vec3 ab = self.b -self.a;
			vec3 pa = p - self.a;
			float t = clamp(dot(ab, pa) / dot(ab, ab), 0.0,1.0);
			return length(((ab*t) + self.a) - p) - self.radius;)")
	)
	template <typename F>
	std::string glslLiteral(const capsule<F>& self) {
		return std::string("capsule") + "(" + vecLiteral<F, 3>(self.a) +", "+vecLiteral<F,3>(self.b)+", "+print(self.radius) +")";
	}
}