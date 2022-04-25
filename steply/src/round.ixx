module;
#define UI_NAME "round"
#include "guiDef.h"
export module round;
import AbstractEditor;
export namespace SDF {
	template <typename F>
	struct round {
		F radius;
	};
	template <typename F>
	inline F sdfUnaryOp(const round<F>& i, F a) {
		return a - i.radius;
	}
	decl_uiName(round, UI_NAME);
	template <typename F>
	round<F> Edit(const round<F>& obj, IEditor<F>* editor, bool* changed) {
		auto r = editor->EditPositive("radius", obj.radius, changed);
		if (changed) {
			return { r };
		}
		return obj;
	}
}