module;
// we use macros in .ixx modules to privately conjoin some compile-time strings
// its fun!
#define UI_NAME "box"
#include "guiDef.h"
#include <string>
#define SNAME UI_NAME
#define SDEF "struct" SNAME " {vec3 dim;};"
#define FNAME "sdfBox"
#define FNBODY R"(
	vec3 d = abs(p)-self.dim;
	vec3 z = vec3(0,0,0);
	vec3 m = min(d,z);
	return length(max(d,z)) + max(m.x,max(m.y,m.z));)"
#define FNDEF decl_glslFunc(FNAME,SNAME,FNBODY);


export module sdfBox;
import imvec;
import string_helpers;
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
		decl_uiName(box, UI_NAME)
		decl_glslInterface(box, SNAME, SDEF, FNAME, FNDEF)
		export template <typename F>
			std::string glslLiteral(const box<F>& self) {
			return std::string(SNAME) + "(" + vecLiteral<F, 3>(self.dim) + ")";
		}
};
