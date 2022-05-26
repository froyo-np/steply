module;
#include <variant>
#include <string>
#include <map>
#include <stack>
#include <iostream>
export module glslVisitor;
import imvec;
import sdflib;
namespace SDF {
	/**/
	export template <typename F>
	class glslHeaderVisitor : public IVisitor<F> {
	protected:
		

		void considerStruct(std::string stName, std::string stDef) {
			if (stName == "empty") {
				// this op has no struct
			}
			else if (stName == "float") {
				// its just a float
			}
			else if (stName == "vec3") {
				// yup its built in guys
			}
			else if (structDefs.count(stName) < 1) {
				// its new lets define it!
				structDefs[stName] = stDef;
			}
		}
		void considerFn(std::string funName, std::string funDef) {

			if (structDefs.count(funName) < 1) {
				// its new lets define it!
				fnDefs[funName] = funDef;
			}
		}
		template <typename pV>
		void helper(pV& p) {
			auto me = this;
			std::visit([me](const auto& arg) {me->considerStruct(glslStructName<F>(arg), glslStructDef<F>(arg)); }, p);
			std::visit([me](const auto& arg) {me->considerFn(glslFnName<F>(arg), glslFnDef<F>(arg)); }, p);
		}
	public:
		std::map<std::string, std::string> structDefs;
		std::map<std::string, std::string> fnDefs;
		
		// for debugging
		void blurt() {
			for (auto a : structDefs) {
				std::cout << a.first << "--->" << a.second << std::endl;
			}
			for (auto a : fnDefs) {
				std::cout << a.first << "--->" << a.second << std::endl;
			}
		}
		virtual void visitUp(BinaryNode<F>* node, binOpVariant<F>& payload) {helper(payload); }
		virtual void visitUp(UnaryNode<F>* node, unaryOpVariant<F>& payload) { helper(payload); }
		virtual void visitUp(DomainNode<F>* node, domainOpVariant<F>& payload) { helper(payload); }

		virtual void visitDown(BinaryNode<F>* node, binOpVariant<F>& payload) { }
		virtual void visitDown(UnaryNode<F>* node, unaryOpVariant<F>& payload) { }
		virtual void visitDown(DomainNode<F>* node, domainOpVariant<F>& payload) { }

		virtual void visitLeaf(LeafNode<F>* node, shapeVariant<F>& payload) { helper(payload); }
	};
	
	export template <typename F>
	class glslDirectCallVisitor : public IVisitor<F> {
	protected:
		std::stack<std::string> subExprStack;
		std::stack<std::string> pointExprStack;

		std::string popExpr() {
			auto t = subExprStack.top();
			subExprStack.pop();
			// aww yea move semantics
			return t;
		}
		void pushExpr(std::string&& t) {
			subExprStack.push(t);
		}
		void pushExpr(std::string& t) {
			subExprStack.push(t);
		}

		std::string getPointExpr() {
			auto t = pointExprStack.top();
			return t;
		}
		void popPointExpr() {
			pointExprStack.pop();
		}
		void pushPointExpr(std::string& str) {
			pointExprStack.push(str);
		}
		void pushPointExpr(std::string&& str) {
			pointExprStack.push(str);
		}
		template <typename pV>
		std::string literalFor(pV& payload) {
			return std::visit([](const auto& arg) {return glslLiteral(arg); }, payload);
		}
		template <typename pV>
		std::string getFnName(pV& payload) {
			return std::visit([](const auto& arg) {return glslFnName(arg); }, payload);
		}
	public:
		glslDirectCallVisitor(std::string pExpr) {
			pointExprStack.push(pExpr);
		}
		std::string getExpr() {
			return subExprStack.top();
		}
		void visitLeaf(LeafNode<F>* node, shapeVariant<F>& payload) {
			std::string selfValue = literalFor<shapeVariant<F>>(payload);
			std::string call = getFnName<shapeVariant<F>>(payload) + "(" + (selfValue.size() > 0 ? selfValue + ", " : "") + getPointExpr() + ")";
			pushExpr(call);
		}
		
		void visitDown(UnaryNode<F>* node, unaryOpVariant<F>& payload) {
		}
		void visitUp(UnaryNode<F>* node, unaryOpVariant<F>& payload) {
			std::string selfValue = literalFor<unaryOpVariant<F>>(payload);
			std::string call = getFnName<unaryOpVariant<F>>(payload) + "(" + (selfValue.size() > 0 ? selfValue + ", " : "") + popExpr() + ")";
			pushExpr(call);
		}
		
		void visitDown(DomainNode<F>* node, domainOpVariant<F>& payload) {
			std::string selfValue = literalFor<domainOpVariant<F>>(payload);
			std::string call = getFnName<domainOpVariant<F>>(payload) + "(" + (selfValue.size() > 0 ? selfValue + ", " : "") + getPointExpr() + ")";
			pushPointExpr(call);
		}
		void visitUp(DomainNode<F>* node, domainOpVariant<F>& payload) {
			popPointExpr();
		}
		
		void visitDown(BinaryNode<F>* node, binOpVariant<F>& payload) { }
		void visitUp(BinaryNode<F>* node, binOpVariant<F>& payload) {
			auto rExp = popExpr();
			auto lExp = popExpr();
			std::string selfValue = literalFor<binOpVariant<F>>(payload);
			std::string call = getFnName<binOpVariant<F>>(payload) + "(" + (selfValue.size() > 0 ? selfValue + ", " : "") + lExp + ", " + rExp+ ")";
			pushExpr(call);
		}
	};
	/**/
};