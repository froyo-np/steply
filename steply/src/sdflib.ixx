module;
#include <memory>
#include <variant>
#include <vector>
#include <array>
export module sdflib;
import imvec;
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

	export template <typename F>
	using binOpVariant = std::variant<union_sdf<F>, smoothUnion<F>, intersect<F>, smoothIntersect<F>, subtract<F>, smoothSubtract<F>>;
	
	export template <typename F>
	using unaryOpVariant = std::variant<round<F>>;

	export template <typename F>
	using domainOpVariant = std::variant<move<F>, repeat<F>>;

	export template <typename F>
	using shapeVariant = std::variant<cone<F>, box<F>, torus<F>, sphere<F>,capsule<F>,hexPrism<F>,cylinder<F>>;

	template <typename F>
	class IVisitor;

	export template <typename F>
	class INode {
	public:
		virtual void visit(IVisitor<F>* visitor) = 0;

	};
	export template <typename F>
	class BinaryNode : public INode<F> {
	protected:
		binOpVariant<F> payload;
		std::unique_ptr<INode<F>> lhs;
		std::unique_ptr<INode<F>> rhs;
	public:
		template <typename P>
		BinaryNode(const P& p, std::unique_ptr<INode<F>>&& l, std::unique_ptr<INode<F>>&& r) : payload(p), lhs(std::move(l)), rhs(std::move(r)) {}
		virtual void visit(IVisitor<F>* visitor) {
			visitor->visitDown(this, payload);
			lhs->visit(visitor);
			rhs->visit(visitor);
			visitor->visitUp(this, payload);
		}
	};
	export template <typename F>
	class UnaryNode : public INode<F> {
	protected:
		unaryOpVariant<F> payload;
		std::unique_ptr<INode<F>> child;
	public:
		template <typename P>
		UnaryNode(const P& p, std::unique_ptr<INode<F>>&& c) : payload(p), child(std::move(c)) {}
		virtual void visit(IVisitor<F>* visitor) {
			visitor->visitDown(this, payload);
			child->visit(visitor);
			visitor->visitUp(this, payload);
		}
	};
	export template <typename F>
	class DomainNode: public INode<F> {
	protected:
		domainOpVariant<F> payload;
		std::unique_ptr<INode<F>> child;
	public:
		template <typename P>
		DomainNode(const P& p, std::unique_ptr<INode<F>>&& c) : payload(p), child(std::move(c)) {}
		virtual void visit(IVisitor<F>* visitor) {
			visitor->visitDown(this, payload);
			child->visit(visitor);
			visitor->visitUp(this, payload);
		}
	};
	export template <typename F>
	class LeafNode : public INode<F> {
	protected:
		shapeVariant<F> payload;
	public:
		template <typename P>
		LeafNode(const P& p) : payload(p) {}
		virtual void visit(IVisitor<F>* visitor) {
			visitor->visitLeaf(this, payload);
		}
	};

	export template <typename F>
	class IVisitor {
	public:
		virtual void visitUp(BinaryNode<F>* node, binOpVariant<F>& payload) = 0;
		virtual void visitUp(UnaryNode<F>* node, unaryOpVariant<F>& payload) = 0;
		virtual void visitUp(DomainNode<F>* node, domainOpVariant<F>& payload) = 0;

		virtual void visitDown(BinaryNode<F>* node, binOpVariant<F>& payload) = 0;
		virtual void visitDown(UnaryNode<F>* node, unaryOpVariant<F>& payload) = 0;
		virtual void visitDown(DomainNode<F>* node, domainOpVariant<F>& payload) = 0;

		virtual void visitLeaf(LeafNode<F>* node, shapeVariant<F>& payload) = 0;
	};
	
	export template <typename F>
	inline auto Union(std::unique_ptr<INode<F>>&& lhs, std::unique_ptr<INode<F>>&& rhs) {
		return std::make_unique<BinaryNode<F>>(union_sdf<F>(), std::move(lhs), std::move(rhs));
	}
	export template <typename F>
	inline auto Union(F radius, std::unique_ptr<INode<F>>&& lhs, std::unique_ptr<INode<F>>&& rhs) {
		return std::make_unique<BinaryNode<F>>(smoothUnion<F>(radius), std::move(lhs), std::move(rhs));
	}
	export template <typename F>
	inline auto Intersect(std::unique_ptr<INode<F>>&& lhs, std::unique_ptr<INode<F>>&& rhs) {
		return std::make_unique<BinaryNode<F>>(intersect<F>(), std::move(lhs), std::move(rhs));
	}
	export template <typename F>
	inline auto Intersect(F radius, std::unique_ptr<INode<F>>&& lhs, std::unique_ptr<INode<F>>&& rhs) {
		return std::make_unique<BinaryNode<F>>(smoothIntersect<F>(radius), std::move(lhs), std::move(rhs));
	}
	export template <typename F>
	inline auto Subtract(std::unique_ptr<INode<F>>&& lhs, std::unique_ptr<INode<F>>&& rhs) {
		return std::make_unique<BinaryNode<F>>(subtract<F>(), std::move(lhs), std::move(rhs));
	}
	export template <typename F>
	inline auto Subtract(F radius, std::unique_ptr<INode<F>>&& lhs, std::unique_ptr<INode<F>>&& rhs) {
		return std::make_unique<BinaryNode<F>>(smoothSubtract<F>(radius), std::move(lhs), std::move(rhs));
	}
	export template <typename F>
	inline auto Move(ivec::vec<F, 3> offset, std::unique_ptr<INode<F>>&& subtree) {
		return std::make_unique<DomainNode<F>>(move<F>(offset), std::move(subtree));
	}
	export template <typename F>
	inline auto Round(F radius, std::unique_ptr<INode<F>>&& subtree) {
		return std::make_unique<UnaryNode<F>>(round<F>(radius), std::move(subtree));
	}
	export template <typename F>
	inline auto Box(ivec::vec<F, 3> dim) {
		return std::make_unique<LeafNode<F>>(box<F>(dim));
	}
	export template <typename F>
	inline auto Cone(F radius, F height) {
		return std::make_unique<LeafNode<F>>(cone<F>(radius, height));
	}
	export template <typename F>
	inline auto Torus(F radius, F thickness) {
		return std::make_unique<LeafNode<F>>(torus<F>(radius, thickness));
	}
	export template <typename F>
	inline auto Sphere(F radius) {
		return std::make_unique<LeafNode<F>>(sphere<F>(radius));
	}
	export template <typename F>
	inline auto Cylinder(F radius, F height) {
		return std::make_unique<LeafNode<F>>(cylinder<F>(radius, height));
	}
	export template <typename F>
	inline auto HexPrism(F radius, F height) {
		return std::make_unique<LeafNode<F>>(hexPrism<F>(radius, height));
	}
	export template <typename F>
	inline auto Capsule(ivec::vec<F, 3> a, ivec::vec<F, 3> b) {
		return std::make_unique<LeafNode<F>>(capsule<F>(a, b));
	}
};
