module;
#define max(a,b) a > b ? a : b
#define abs(a) a >= 0 ? a : -a
#include "guiDef.h"
export module sdfIntersect;
import imvec;
import AbstractEditor;

export namespace SDF {
		template <typename F>
		struct intersect {
			// intentionally empty!
		};
		template <typename F>
		inline F sdfBinaryOp(const intersect<F>& i, F a, F b) {
			return max(a, b);
		}
		template <typename F>
		struct smoothIntersect {
			F radius;
			smoothIntersect() : radius(0.0) {}
			smoothIntersect(F r) : radius(r) {}

		};
		template <typename F>
		inline F sdfBinaryOp(const smoothIntersect<F>& i, F d1, F d2) {
			F k = i.radius;
			F h = max(k - abs(d1 - d2), 0.0);
			return max(d1, d2) + h * (h * 0.25 / k);
		}
		decl_uiName(intersect, "intersect");
		decl_uiName(smoothIntersect, "smooth intersect");

		template <typename F>
		intersect<F> Edit(const intersect<F>& obj, IEditor<F>* editor, bool* changed) {
			return obj;
		}
		template <typename F>
		smoothIntersect<F> Edit(const smoothIntersect<F>& obj, IEditor<F>* editor, bool* changed) {
			auto r = editor->EditPositive("radius", obj.radius, changed);
			if (changed) {
				return { r };
			}
			return obj;
		}
}