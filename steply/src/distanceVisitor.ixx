module;
#include <variant>
export module distanceVisitor;
import imvec;
import sdfNode;

namespace SDF {
	
	export template<typename F, typename GroupType>
	F visitDistance(const typename GroupType::BinaryOp& node, const ivec::vec<F, 3>& p) {
		// visit children first
		F a = visitDistance<F, GroupType>(node.getLhs(), p);
		F b = visitDistance<F, GroupType>(node.getRhs(), p);
		return std::visit(
			[a, b](const auto& arg) {return sdfBinaryOp<F>(arg, a, b); }, node.getPayload());
	}
	export template<typename F, typename GroupType>
	F visitDistance(const typename GroupType::Shape& node, const ivec::vec<F, 3>& p) {
		return std::visit( // deduces arg-type for every variant of shape payload
			[&p](const auto& arg) {return distanceTo<F>(arg, p); }, node.getPayload());
	}
	export template<typename F, typename GroupType>
		F visitDistance(const typename GroupType::UnaryOp& node, const ivec::vec<F, 3>& p) {
		F childDst = visitDistance<F,GroupType>(node.getChild(), p);
		return std::visit( // note that unary ops mess with their child's distance value
			[childDst](const auto& arg) {return sdfUnaryOp<F>(arg, childDst); }, node.getPayload());
	}
	export template<typename F, typename GroupType>
		F visitDistance(const typename GroupType::DomainOp& node, const ivec::vec<F, 3>& p) {
		ivec::vec<F, 3> pnt = std::visit( // wheras domain ops mess with the given test-point p
			[p](const auto& arg) {return sdfDomainOp<F>(arg, p); }, node.getPayload());
		return visitDistance<F, GroupType>(node.getChild(), pnt);
	}
	// IMPORTANT: DEFINERS OF VISITORS that use overload resolution
	// must have the most generic version defined last - (or of course just declare all of them first before defining any)
	export template<typename F, typename GroupType>
	F visitDistance(const typename GroupType::NodeVariant& node, const ivec::vec<F, 3>& p) {
		return std::visit( 
			[&p](const auto& arg) {return visitDistance<F, GroupType>(arg, p); }, node);
	}
};