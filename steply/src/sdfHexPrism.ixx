module;
#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b
#define UI_NAME "hex prism"
#include "guiDef.h"
export module sdfHexPrism;

import imvec;
export namespace SDF {
	using namespace ivec;
	template <typename F>
	struct hexPrism {
		F radius;
		F height;
		hexPrism() : radius(0.5), height(1.0) { }
		hexPrism(F r, F h) : radius(r), height(h) {}

	};
	template <typename F>
	F distanceTo(const hexPrism<F>& self, const vec<F, 3>& p) {
		using vec3 = ivec::vec<F, 3>;
		using vec2 = ivec::vec<F, 2>;
		vec3 k = vec3(-0.8660254, 0.5, 0.57735);
		vec2 h = vec2(self.radius, self.height);
		vec3 p1 = p.abs();
		p1 = vec3(p1.xy() - k.xy() * 2.0 * min(k.xy().dot(p1.xy()), 0.0f), p1.z());

		vec2 d = vec2(
			(p.xy() - vec2(clamp(p.x(), -k.z() * h.x(), k.z() * h.x()), h.x())).length() * sign(p.y() - h.x()),
			p.z() - h.y());

		return min(max(d.x(), d.y()), 0.0f) + vec2::Max(d, vec2(0, 0)).length();
	}
	decl_uiName(hexPrism, UI_NAME);

	
}