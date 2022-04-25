module;
#define UI_NAME "offset"
#include "guiDef.h"
export module move;
import imvec;
import AbstractEditor;

export namespace SDF {

	template <typename F>
	struct move {
		ivec::vec<F, 3> offset;
	};

	template <typename F>
	inline ivec::vec<F, 3> sdfDomainOp(const move<F>& trn, const ivec::vec<F, 3>& pnt) {
		return trn.offset + pnt;
	}
	decl_uiName(move, UI_NAME);

	template <typename F>
	move<F> Edit(const move<F>& obj, IEditor<F>* editor, bool* changed) {
		auto pos = editor->Edit("offset", obj.offset, changed);
		if (changed) {
			return { pos};
		}
		return obj;
	}
};
