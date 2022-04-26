module;
#define UI_NAME "sphere"
#include "guiDef.h"

export module sdfSphere;
import imvec;

export namespace SDF {
	using namespace ivec;
		template <typename F>
		struct sphere {
			F radius;
			sphere() : radius(1.0) {}
			sphere(F r) : radius(r) {}
		};
		template <typename F>
		inline F distanceTo(const sphere<F>& self, const vec<F, 3>& p) {
			return p.length() - self.radius;
		}
		decl_uiName(sphere, UI_NAME);

		
};