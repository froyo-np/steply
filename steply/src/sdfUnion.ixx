module;
#define max(a,b) a > b ? a : b
#define min(a,b) a < b ? a : b
export module sdfUnion;
import imvec;

export namespace SDF {
	template <typename F>
	struct Union {
		// intentionally empty!
	};
	template <typename F>
	inline F sdfBinaryOp(const Union<F>& i, F a, F b) {
		return min(a, b);
	}
	template <typename F>
	struct smoothUnion {
		F radius;
		smoothUnion() : radius(0.0) {}
		smoothUnion(F r) : radius(r) {}

	};
	template <typename F>
	inline F sdfBinaryOp(const smoothUnion<F>& i, F d1, F d2) {
		F r = i.radius;
		vec<F, 2> u = vec<F, 2>(max<F>(0, r - a), max<F>(0, r - b));
		return max(r, min(a, b)) - u.length();
	}
}