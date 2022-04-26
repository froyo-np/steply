module;
#define UI_NAME "box"
#include "guiDef.h"
export module sdfBox;
import imvec;

export namespace SDF {
		using namespace ivec;
		template <typename F>
		struct box {
			ivec::vec<F, 3> dim;
			box() : dim(vec<F, 3>(1, 1, 1)) {}
			box(vec<F, 3> size) : dim(size) {}
			
		};
		template <typename F>
		F distanceTo(const box<F>& self, const vec<F, 3>& p) {
			vec<F, 3> d = p.abs() - self.dim;
			vec<F, 3> z(0, 0, 0);
			return d.max(z).length() + d.min(z).maxComponent();
		}
		decl_uiName(box,UI_NAME)

};
