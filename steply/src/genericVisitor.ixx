module;
#include <variant>

export module genericVisitor;
import sdfNode;

namespace SDF {

	export template <typename F, typename GroupType, typename ConcreteVisitor>
	class genericVisitor {
	protected:
		genericVisitor() {}
	public:
		void visit(const typename GroupType::Shape& node) {
			auto me = static_cast<ConcreteVisitor*>(this);
			me->visitDown(node);
			me->visitUp(node);
		}
		void visit(const typename GroupType::BinaryOp& node) {
			auto me = static_cast<ConcreteVisitor*>(this);
			me->visitDown(node);
			visit(node.getLhs());
			visit(node.getRhs());
			me->visitUp(node);
		
		}
		void visit(const typename GroupType::UnaryOp& node) {
			auto me = static_cast<ConcreteVisitor*>(this);
			me->visitDown(node);
			visit(node.getChild());
			me->visitUp(node);
			
		}
		void visit(const typename GroupType::DomainOp& node) {
			auto me = static_cast<ConcreteVisitor*>(this);
			me->visitDown(node);
			visit(node.getChild());
			me->visitUp(node);
		
		}
		void visit(const typename GroupType::NodeVariant& node) {
			auto me = static_cast<ConcreteVisitor*>(this);
			std::visit([me](const auto& n) {me->visit(n); }, node);
		}
	};
};