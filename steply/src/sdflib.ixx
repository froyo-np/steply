module;
#include <memory>
#include <variant>
#include <vector>
export module sdflib;
import imvec;
import sdfNode;
// prims
export import sdfBox;
export import sdfCone;
export import sdfSphere;
export import sdfTorus;

// ops
export import sdfIntersect;
export import sdfSubtract;
export import sdfUnion;
export import round;
export import move;

namespace SDF {

	export template <typename F, typename... UserDefinedBinOpPayloads>
	using binOpVariant = std::variant<union_sdf<F>, smoothUnion<F>, intersect<F>, smoothIntersect<F>, subtract<F>, smoothSubtract<F>, UserDefinedBinOpPayloads...>;

	export template <typename F, typename... MoreUnaryOpPayloads>
	using unaryOpVariant = std::variant<round<F>, MoreUnaryOpPayloads...>;

	export template <typename F, typename ...ExtraDomainOpPayloads>
	using domainOpVariant = std::variant<move<F>, ExtraDomainOpPayloads...>;

	export template <typename F, typename... EvenMoreSDFShapes>
	using shapeVariant = std::variant<cone<F>, box<F>, torus<F>, sphere<F>, EvenMoreSDFShapes...>;

	// at some point, the user of this library must declare a subclass of sdfTreeNode, so that they can actually implement some of this stuff, and also
	// have the chance to define their own node types. this does not by them much...
	export template <typename F, typename NodeGroupType>
	class SDFLIB {
	public:
		// TODO more friendly-name factory-style methods for known primitives
		static auto Union(typename NodeGroupType::NodeVariant&& lhs, typename NodeGroupType::NodeVariant&& rhs) {
			//return typename NodeGroupType::BinaryOp<typename NodeGroupType::binVariants>(union_sdf<F>(), std::forward(lhs), std::forward(rhs));
			return typename NodeGroupType::BinaryOp(union_sdf<F>(), std::move(lhs), std::move(rhs));
		}
		static auto Box(ivec::vec<F, 3> dim) {
			return typename NodeGroupType::Shape(box<F>(dim));
		}
	};
};
