module;
#define UI_NAME "torus"
#include "guiDef.h"
export module sdfTorus;

import imvec;

export namespace SDF {
	using namespace ivec;
		template <typename F>
		struct torus {
			F radius;
			F thickness;
			torus() : radius(0.5), thickness(1.0) { }
			torus(F r, F t) : radius(r), thickness(t) {}
			
		};
		template <typename F>
		F distanceTo(const torus<F>& self, const vec<F, 3>& p) {
			F x = p.xz().length() - self.radius;
			vec<F, 2> s(x, p.y());
			return s.length() - self.thickness;
		}
		decl_uiName(torus, UI_NAME);
		
		
};