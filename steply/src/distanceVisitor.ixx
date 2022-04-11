module;
#include <variant>
export module distanceVisitor;
import imvec;
import sdfNode;

namespace SDF {
	// a distance visitor must:
	// define a visit fn for all variants of node-type
	// visitors may be free functions, or they may be objects
	// that get passed around. NO RULES!
	// note that since the class of nodes in a specific use case of this library isn't defined
	// until the user defines it - adding node-classes to the tree-group type will require you to write a
	// visitor for that type

	export template<typename F, typename GroupType>
	F visitDistance(const typename GroupType::BinaryOp& node, const ivec::vec<F, 3>& p) {
		// visit children first
		F a = visitDistance<F, GroupType>(node.getLhs(), p);
		F b = visitDistance<F, GroupType>(node.getRhs(), p);
		return std::visit( // all 6 types of binOp can be deduced!
			[a, b](const auto& arg) {return sdfBinaryOp<F>(arg, a, b); }, node.getPayload());
	}
	export template<typename F, typename GroupType>
	F visitDistance(const typename GroupType::Shape& node, const ivec::vec<F, 3>& p) {
		return std::visit( // all 6 types of binOp can be deduced!
			[&p](const auto& arg) {return distanceTo<F>(arg, p); }, node.getPayload());
	}
	export template<typename F, typename GroupType>
		F visitDistance(const typename GroupType::UnaryOp& node, const ivec::vec<F, 3>& p) {
		F childDst = visitDistance<F,GroupType>(node.getChild(), p);
		return std::visit(
			[childDst](const auto& arg) {return sdfUnaryOp<F>(arg, childDst); }, node.getPayload());
	}
	export template<typename F, typename GroupType>
		F visitDistance(const typename GroupType::DomainOp& node, const ivec::vec<F, 3>& p) {
		ivec::vec<F, 3> pnt = std::visit(
			[p](const auto& arg) {return sdfDomainOp<F>(arg, p); }, node.getPayload());
		return visitDistance<F, GroupType>(node.getChild(), pnt);
	}

	export template<typename F, typename GroupType>
	F visitDistance(const typename GroupType::NodeVariant& node, const ivec::vec<F, 3>& p) {
		return std::visit(
			[&p](const auto& arg) {return visitDistance<F, GroupType>(arg, p); }, node);
	}
};