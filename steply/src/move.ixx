module;

export module move;
import imvec;


export namespace SDF {

	template <typename F>
	struct move {
		ivec::vec<F, 3> offset;
	};

	template <typename F>
	inline ivec::vec<F, 3> sdfDomainOp(const move<F>& trn, const ivec::vec<F, 3>& pnt) {
		return trn.offset + pnt;
	}

};
