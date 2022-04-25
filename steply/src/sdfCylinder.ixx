module;
#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b
#define UI_NAME "cylinder"
#include "guiDef.h"
export module sdfCylinder;
import AbstractEditor;
import imvec;
export namespace SDF {
	using namespace ivec;
	template <typename F>
	struct cylinder {
		F radius;
		F height;
		cylinder() : radius(0.5), height(1.0) { }
		cylinder(F r, F h) : radius(r), height(h) {}
		
	};
	template <typename F>
	F distanceTo(const cylinder<F>& self, const vec<F, 3>& p) {
		F d = p.xz().length() - self.radius;
		return max(d, p.abs().y() - self.height);
	}
	decl_uiName(cylinder, UI_NAME);

	template <typename F>
	cylinder<F> Edit(const cylinder<F>& obj, IEditor<F>* editor, bool* changed) {
		auto r = editor->EditPositive("radius", obj.radius, changed);
		auto h = editor->EditPositive("height", obj.height, changed);
		if (changed) {
			return { r,h };
		}
		return obj;
	}
}