module;

// TODO feel free to use C-style #defines to concatenate
// string literals - a fun, safe, and private way to keep GLSL
// code right next to the math / c++ that touches it!

export module sdfBox;
import imvec;

/// the SDF of a 3D box ///

// all SDF things, in this case a primitive,
// must have both a C++ evaluation function
// and some strings for GLSL code-generation -(TODO)

export namespace SDF {
		using namespace ivec;
		template <typename F>
		struct box {
			ivec::vec<F, 3> dim;
			box() : dim(vec<F, 3>(1, 1, 1)) {}
			box(vec<F, 3> size) : dim(size) {}
			/*Box3 getBound() const {
				return Box3(dim / -1.0, dim / 1.0);
			}*/
		};
		template <typename F>
		inline F distanceTo(const box<F>& self, const vec<F, 3>& p) {
			vec<F, 3> d = p.abs() - self.dim;
			vec<F, 3> z(0, 0, 0);
			return d.max(z).length() + d.min(z).maxComponent();
		}
};
