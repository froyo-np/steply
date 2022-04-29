module;
#include <memory>
#include <variant>
#include <vector>
#include <array>
export module sdflib;
import imvec;
import sdfNode;
// prims
export import sdfBox;
export import sdfCone;
export import sdfSphere;
export import sdfTorus;
export import sdfHexPrism;
export import sdfCapsule;
export import sdfCylinder;
// ops
export import sdfIntersect;
export import sdfSubtract;
export import sdfUnion;
export import round;
export import move;
export import repeat;

namespace SDF {

	export template <typename F, typename... UserDefinedBinOpPayloads>
	using binOpVariant = std::variant<union_sdf<F>, smoothUnion<F>, intersect<F>, smoothIntersect<F>, subtract<F>, smoothSubtract<F>, UserDefinedBinOpPayloads...>;
	

	export template <typename F, typename... MoreUnaryOpPayloads>
	using unaryOpVariant = std::variant<round<F>, MoreUnaryOpPayloads...>;

	export template <typename F, typename ...ExtraDomainOpPayloads>
	using domainOpVariant = std::variant<move<F>, repeat<F>, ExtraDomainOpPayloads...>;

	export template <typename F, typename... EvenMoreSDFShapes>
	using shapeVariant = std::variant<cone<F>, box<F>, torus<F>, sphere<F>,capsule<F>,hexPrism<F>,cylinder<F>, EvenMoreSDFShapes...>;

	// at some point, the user of this library must declare a subclass of sdfTreeNode, so that they can actually implement some of this stuff, and also
	// have the chance to define their own node types. this does not by them much...
	export template <typename F, typename NodeGroupType>
	class SDFLIB {
	public:
		static inline auto Union(typename NodeGroupType::NodeVariant&& lhs, typename NodeGroupType::NodeVariant&& rhs) {
			return typename NodeGroupType::BinaryOp(union_sdf<F>(), std::move(lhs), std::move(rhs));
		}

		static inline auto Union(F radius, typename NodeGroupType::NodeVariant&& lhs, typename NodeGroupType::NodeVariant&& rhs) {
			return typename NodeGroupType::BinaryOp(smoothUnion<F>(radius), std::move(lhs), std::move(rhs));
		}

		static inline auto Intersect(typename NodeGroupType::NodeVariant&& lhs, typename NodeGroupType::NodeVariant&& rhs) {
			return typename NodeGroupType::BinaryOp(intersect<F>(), std::move(lhs), std::move(rhs));
		}

		static inline auto Intersect(F radius, typename NodeGroupType::NodeVariant&& lhs, typename NodeGroupType::NodeVariant&& rhs) {
			return typename NodeGroupType::BinaryOp(smoothIntersect<F>(radius), std::move(lhs), std::move(rhs));
		}

		static inline auto Subtract(typename NodeGroupType::NodeVariant&& lhs, typename NodeGroupType::NodeVariant&& rhs) {
			return typename NodeGroupType::BinaryOp(subtract<F>(), std::move(lhs), std::move(rhs));
		}

		static inline auto Subtract(F radius, typename NodeGroupType::NodeVariant&& lhs, typename NodeGroupType::NodeVariant&& rhs) {
			return typename NodeGroupType::BinaryOp(smoothSubtract<F>(radius), std::move(lhs), std::move(rhs));
		}

		static inline auto Move(ivec::vec<F,3> offset, typename NodeGroupType::NodeVariant&& subtree) {
			return typename NodeGroupType::DomainOp(move<F>(offset), std::move(subtree));
		}

		static inline auto Round(F radius, typename NodeGroupType::NodeVariant&& subtree) {
			return typename NodeGroupType::UnaryOp(round<F>(radius), std::move(subtree));
		}

		static inline auto Box(ivec::vec<F, 3> dim) {
			return typename NodeGroupType::Shape(box<F>(dim));
		}
		static inline auto Cone(F radius, F height) {
			return typename NodeGroupType::Shape(cone<F>(radius, height));
		}
		static inline auto Torus(F radius, F thickness) {
			return typename NodeGroupType::Shape(torus<F>(radius, thickness));
		}
		static inline auto Sphere(F radius) {
			return typename NodeGroupType::Shape(sphere<F>(radius));
		}

		static inline auto Cylinder(F radius, F height) {
			return typename NodeGroupType::Shape(cylinder<F>(radius,height));
		}

		static inline auto HexPrism(F radius, F height) {
			return typename NodeGroupType::Shape(hexPrism<F>(radius, height));
		}

		static inline auto Capsule(ivec::vec<F,3> a, ivec::vec<F,3> b) {
			return typename NodeGroupType::Shape(capsule<F>(a,b));
		}
	};
};
