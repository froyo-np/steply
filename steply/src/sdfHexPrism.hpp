#pragma once
#include "guiDef.h"
#include <string>

#include "string_helpers.h"
#include "imvec\imvec.hpp"
namespace SDF {
	using namespace imvec;
	template <typename F>
	struct hexPrism {
		F radius;
		F height;
		hexPrism() : radius(0.5), height(1.0) { }
		hexPrism(F r, F h) : radius(r), height(h) {}

	};
	template <typename F>
	F distanceTo(const hexPrism<F>& self, const vec<F, 3>& p) {
		using vec3 = imvec::vec<F, 3>;
		using vec2 = imvec::vec<F, 2>;
		vec3 k = vec3(-0.8660254, 0.5, 0.57735);
		vec2 h = vec2(self.radius, self.height);
		vec3 p1 = p.abs();
		p1 = vec3(p1.xy() - k.xy() * 2.0 * min(k.xy().dot(p1.xy()), 0.0f), p1.z());

		vec2 d = vec2(
			(p.xy() - vec2(clamp(p.x(), -k.z() * h.x(), k.z() * h.x()), h.x())).length() * sign(p.y() - h.x()),
			p.z() - h.y());

		return min(max(d.x(), d.y()), 0.0f) + vec2::Max(d, vec2(0, 0)).length();
	}
	decl_uiName(hexPrism, "hex")
	decl_glslInterface(hexPrism, "hex", "struct hex {float radius; float height;};", "sdfHex", 
		decl_glslFunc("sdfHex","hex", R"(
			vec2 h = vec2(self.radius,self.height);
			const vec3 k = vec3(-0.8660254, 0.5, 0.57735);
			p = abs(p);
			p.xy -= 2.0*min(dot(k.xy, p.xy), 0.0)*k.xy;
			vec2 d = vec2(
				length(p.xy-vec2(clamp(p.x,-k.z*h.x,k.z*h.x), h.x))*sign(p.y-h.x),
				p.z-h.y );
			return min(max(d.x,d.y),0.0) + length(max(d,0.0));
			)")
	)
	template <typename F>
	std::string glslLiteral(const hexPrism<F>& self) {
		return std::string("hex") + "(" + print(self.radius) + ", " + print(self.height) + ")";
	}
}