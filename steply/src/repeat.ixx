module;
#define UI_NAME "repeat"
#include "guiDef.h"
export module repeat;
import imvec;

import AbstractEditor;
export namespace SDF {
	using namespace ivec;
	template <typename F>
	struct repeat {
		vec<F, 3> reps;
		vec<F, 3> stepSize;
		repeat(const vec<F, 3>& counts, const vec<F, 3>& sizes) : reps(counts), stepSize(sizes) {}
		repeat() : reps(vec<F, 3>(3, 1, 3)), stepSize(vec<F, 3>(100, 100, 100)) {}
	};

	template <typename F>
	inline vec<F, 3> sdfDomainOp(const repeat<F>& t, const ivec::vec<F, 3>& p) {
		using vec3 = vec<F, 3>;
		vec3 c = t.stepSize;
		vec3 l = t.reps;
		vec3 k = p - c * vec3::Min(vec3::Max((p / c).round(), l * -1.0), l);
		return k;
	}
	decl_uiName(repeat, UI_NAME);

	template <typename F>
	repeat<F> Edit(const repeat<F>& obj, IEditor<F>* editor, bool* changed) {
		auto reps = editor->EditPositive("steps", obj.reps, changed);
		auto size = editor->EditPositive("step size", obj.stepSize, changed);
		if (changed) {
			return { reps, size };
		}
		return obj;
	}
};

