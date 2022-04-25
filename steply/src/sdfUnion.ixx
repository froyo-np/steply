module;
#define max(a,b) a > b ? a : b
#define min(a,b) a < b ? a : b
#include "guiDef.h"
export module sdfUnion;
import imvec;
import AbstractEditor;
export namespace SDF {
	// 'union' is of course a keyword - blerg
	template <typename F>
	struct union_sdf {
		// intentionally empty!
	};
	template <typename F>
	inline F sdfBinaryOp(const union_sdf<F>& i, F a, F b) {
		return min(a, b);
	}
	template <typename F>
	struct smoothUnion {
		F radius;
		smoothUnion() : radius(0.0) {}
		smoothUnion(F r) : radius(r) {}

	};
	template <typename F>
	inline F sdfBinaryOp(const smoothUnion<F>& i, F a, F b) {
		F r = i.radius;
		ivec::vec<F, 2> u = ivec::vec<F, 2>(max(0, r - a), max(0, r - b));
		return max(r, min(a, b)) - u.length();
	}
	decl_uiName(union_sdf, "union");
	decl_uiName(smoothUnion, "smooth union");

	template <typename F>
	union_sdf<F> Edit(const union_sdf<F>& obj, IEditor<F>* editor, bool* changed) {
		return obj;
	}
	template <typename F>
	smoothUnion<F> Edit(const smoothUnion<F>& obj, IEditor<F>* editor, bool* changed) {
		auto r = editor->EditPositive("radius", obj.radius, changed);
		if (changed) {
			return { r };
		}
		return obj;
	}
}