import imvec;
import distanceVisitor;
import sdflib;
#include <vector>
#include <iostream>
#include <memory>
int main() {
	using namespace ivec;
	
	vec<float, 3> test(1,2,3);
	std::cerr << (test*test).y() << std::endl;
	/*

	SDF::box<float> b(vec<float, 3>(1, 2, 3));
	std::cout << SDF::distanceTo<float>(b, test) << std::endl;
	SDF::cone<float> c(0.5, 1.0);
	SDF::union_sdf<float> i = {};
	SDF::smoothSubtract<float> ss(0.01);
	std::cout << SDF::sdfBinaryOp<float>(ss, SDF::distanceTo<float>(SDF::torus<float>(0.5,0.2),test), SDF::sdfBinaryOp<float>(i, SDF::distanceTo<float>(b, test), SDF::distanceTo<float>(c, test))) << std::endl;

	SDF::SDFLIB<float> LIB;
	auto SS = LIB.BinOp<SDF::union_sdf<float>>({}, LIB.Cone(c), LIB.Box(b));
	std::cout <<"yay magic " << SS->getDistance(test) << std::endl;		
	
	using sdf = SDF::Node<float>;
	auto innerBin = SDF::binOp<float>(SDF::union_sdf<float>(), sdf(SDF::box<float>(test)), sdf(SDF::box<float>(test)));
	auto u = sdf(SDF::binOp<float>(SDF::union_sdf<float>(), sdf(SDF::box<float>(test)), sdf(SDF::box<float>(test))));
	std::cout << SDF::distanceTo<float>(innerBin, test);
	auto b = sdf(SDF::box<float>(test));
	//SDF::distanceTo<float>(b, test);
	std::vector<SDF::primOpVariant<float>> prims({ SDF::cone<float>(0.3,1.0), SDF::torus<float>(0.3,1.0),SDF::box<float>(test) });
	std::vector<float> what;
	for (auto i : prims) {
		//std::cout << SDF::visitPrim<float>(i, test) << std::endl;
		//what.push_back(SDF::visitPrim<float>(i, test));
		what.push_back(SDF::visitDistance<SDF::primOpVariant<float>, float>(i, test));

	}
	std::cout << "yay double magic" << std::endl;
	*/
	SDF::sdfLib<float> lib;
	auto b = SDF::box<float>{ test };
	std::cout << "yaya" << SDF::distanceTo<float>(b, test);
	auto u = lib.transform(SDF::move<float>{test}, lib.modify(SDF::round<float>(0.1f), lib.join(SDF::union_sdf<float>({}), SDF::box<float>{test}, SDF::cone(0.5f, 1.0f))));
	std::cout << "yay: " << SDF::visitDistance<float>(u, test);
};