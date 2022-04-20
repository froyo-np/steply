module;
#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b
export module sdfCapsule;

import imvec;
export namespace SDF {
	using namespace ivec;
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
}