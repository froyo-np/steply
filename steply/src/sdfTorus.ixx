module;
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
			/*Box3 getBound() const {
				return Box3(Vec3(-radius, -thickness, -radius), Vec3(radius, thickness, radius));
			}*/
		};
		template <typename F>
		F distanceTo(const torus<F>& self, const vec<F, 3>& p) {
			F x = p.xz().length() - self.radius;
			vec<F, 2> s(x, p.y());
			return s.length() - self.thickness;
		}
};