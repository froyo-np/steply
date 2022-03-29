module;
#define max(a,b) a > b ? a : b
#define min(a,b) a < b ? a : b
export module sdfSubtract;
import imvec;

export namespace SDF {
	template <typename F>
	struct Subtract {
		// intentionally empty!
	};
	template <typename F>
	inline F sdfBinaryOp(const Subtract<F>& i, F a, F b) {
		return max(a, -b);
	}
	template <typename F>
	struct smoothSubtract {
		F radius;
		smoothSubtract() : radius(0.0) {}
		smoothSubtract(F r) : radius(r) {}

	};
	template <typename F>
	inline F sdfBinaryOp(const smoothSubtract<F>& i, F d1, F d2) {
		F k = i.radius;
		F h = max(k - abs(-b - a), 0.0);
		return max(-b, a) + h * h * 0.25 / k;
	}
}