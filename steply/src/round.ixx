export module round;

export namespace SDF {
	template <typename F>
	struct round {
		F radius;
	};
	template <typename F>
	inline F sdfUnaryOp(const round<F>& i, F a) {
		return a - i.radius;
	}
}