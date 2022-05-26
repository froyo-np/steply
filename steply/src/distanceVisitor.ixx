module;
#include <variant>
#include <stack>
export module distanceVisitor;
import imvec;
import sdflib;

namespace SDF {
	
	export template <typename F>
	class DistanceVisitor : public IVisitor<F> {
		using vec3 = ivec::vec<F, 3>;
	protected:
		std::stack<vec3> pStack;
		std::stack<F> dstStack;

	public:
		virtual void visitUp(BinaryNode<F>* node, binOpVariant<F>& payload) {
			auto rRes = dstStack.top();
			dstStack.pop();
			auto lRes = dstStack.top();
			dstStack.pop();
			dstStack.push_back(std::visit([lRes, rRes](const auto& arg) {return sdfBinOp(arg, lRes, rRes); }, payload));
		};
		virtual void visitUp(UnaryNode<F>* node, unaryOpVariant<F>& payload) {
			auto dst = dstStack.top();
			dstStack.pop();
			dstStack.push_back(std::visit([dst](const auto& arg) {return sdfUnaryOp(arg, dst); }, payload));
		};
		virtual void visitUp(DomainNode<F>* node, domainOpVariant<F>& payload) {
			pStack.pop();
		};

		virtual void visitDown(BinaryNode<F>* node, binOpVariant<F>& payload) {};
		virtual void visitDown(UnaryNode<F>* node, unaryOpVariant<F>& payload) {};
		virtual void visitDown(DomainNode<F>* node, domainOpVariant<F>& payload) {
			auto p = pStack.top();
			pStack.push_back(std::visit([p](const auto& arg) {return sdfDomainOp(arg, p); }, payload));
		}

		virtual void visitLeaf(LeafNode<F>* node, shapeVariant<F>& payload) {
			auto p = pStack.top();
			dstStack.push_back(std::visit([p](const auto& arg) {return distanceTo(arg, p); }, payload));
		}
	};
};