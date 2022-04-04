module;
#include <variant>
export module distanceVisitor;
import sdflib;
import imvec;

namespace SDF {

	export template <typename F>
	F visitDistance(const LeafOrNode<F>& self, const ivec::vec<F, 3>& p);
	template <typename F>
	F distanceTo(const BinOp<F>& self, const ivec::vec<F, 3>& p);
	template <typename F>
	F distanceTo(const UnaryOp<F>& self, const ivec::vec<F, 3>& p);
	template <typename F>
	F distanceTo(const NodeVariants<F>& self, const ivec::vec<F, 3>& p);
	template <typename F>
	F distanceTo(const primOpVariant<F>& prim, const ivec::vec<F, 3>& pnt);
	/// Implementations to follow ///

	template <typename F>
	F distanceTo(const BinOp<F>& self, const ivec::vec<F, 3>& p) {
		F a = visitDistance<F>(self.getLhs(), p);
		F b = visitDistance<F>(self.getRhs(), p);
		return std::visit( // all 6 types of binOp can be deduced!
			[a, b](const auto& arg) {return sdfBinaryOp<F>(arg, a, b); }, self.getPayload());
	}
	template <typename F>
	F distanceTo(const UnaryOp<F>& self, const ivec::vec<F, 3>& p) {
		F childDst = visitDistance<F>(self.getChild(), p);
		return std::visit(
			[childDst](const auto& arg) {return sdfUnaryOp<F>(arg, childDst); }, self.getPayload());
	}

	template <typename F>
	F distanceTo(const DomainOp<F>& self, const ivec::vec<F, 3>& p) {
		ivec::vec<F,3> pnt = std::visit(
			[p](const auto& arg) {return sdfDomainOp<F>(arg, p); }, self.getPayload());
		return visitDistance<F>(self.getChild(), pnt);
	}

	template <typename F>
	F distanceTo(const NodeVariants<F>& self, const ivec::vec<F, 3>& p) {
		return std::visit( // BinOps, UnaryOps, DomainOps
			[&p](const auto& arg) {return distanceTo<F>(arg, p); }, self);
	}

	// the primitive-op variant distanceTo fn
	template <typename F>
	F distanceTo(const primOpVariant<F>& prim, const ivec::vec<F, 3>& pnt) {
		return std::visit( // box, sphere, torus, etc...
			[&pnt](const auto& unwrapped) {return SDF::distanceTo<F>(unwrapped, pnt); }
		, prim);
	}
	template <typename F>
	F visitDistance(const LeafOrNode<F>& self, const ivec::vec<F, 3>& p) {
		return std::visit( // leaves, nodes
			[&p](const auto& arg) {return distanceTo<F>(arg, p); }, self);
	}
};