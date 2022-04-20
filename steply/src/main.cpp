import imvec;
import distanceVisitor;
import imguiVisitor;
import sdflib;
import sdfNode;
#include <vector>
#include <iostream>
#include <memory>

using namespace SDF;

using sdfNode = sdfTreeGroup<binOpVariant<float>, unaryOpVariant<float>, domainOpVariant<float>, shapeVariant<float>>;
using sdflib = SDFLIB<float, sdfNode>;

int main() {
	using namespace ivec;
	
	vec<float, 3> test(1,2,3);
	std::cerr << (test*test).y() << std::endl;

	auto hey = sdflib::Union(sdflib::Box(test), sdflib::Box(test));
	SDF::guiVisit<float, sdfNode>(hey);
	std::cerr << visitDistance<float, sdfNode>(sdflib::Union(sdflib::Box(test), sdflib::Box(test)), test);
};