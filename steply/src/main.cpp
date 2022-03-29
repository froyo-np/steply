import imvec;
import sdfBox;
import sdfCone;
import sdfIntersect;
#include <iostream>
int main() {
	using namespace ivec;
	
	vec<float, 3> test(1,2,3);
	std::cout << (test*test).y() << std::endl;
	SDF::box<float> b(vec<float, 3>(1, 2, 3));
	std::cout << SDF::distanceTo<float>(b, test) << std::endl;
	SDF::cone<float> c(0.5, 1.0);
	SDF::intersect<float> i = {};
	std::cout << SDF::sdfBinaryOp<float>(i, SDF::distanceTo<float>(b, test), SDF::distanceTo<float>(c, test)) << std::endl;
};