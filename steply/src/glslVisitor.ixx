module;
#include <variant>
#include <string>
#include <map>
#include <stack>
#include <iostream>
export module glslVisitor;
import imvec;
import sdfNode;
import genericVisitor;
import sdflib;

namespace SDF {
	export template <typename F, typename GroupType>
	class glslHeaderVisitor : public genericVisitor<F, GroupType, glslHeaderVisitor<F,GroupType>> {
	protected:
		std::map<std::string, std::string> structDefs;
		std::map<std::string, std::string> fnDefs;

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
	public:
		template <typename NodeType>
		void visitUp(const NodeType& node) {
			auto me = this;
			std::visit([me](const auto& arg) {me->considerStruct(glslStructName<F>(arg), glslStructDef<F>(arg)); }, node.getPayload());
			std::visit([me](const auto& arg) {me->considerFn(glslFnName<F>(arg), glslFnDef<F>(arg)); }, node.getPayload());
		}
		template <typename NodeType>
		void visitDown(const NodeType& node) {
			// do nothing!
		}
		// for debugging
		void blurt() {
			for (auto a : structDefs) {
				std::cout << a.first << "--->" << a.second << std::endl;
			}
			for (auto a : fnDefs) {
				std::cout << a.first << "--->" << a.second << std::endl;
			}
		}
	};
	
	export template <typename F, typename GroupType>
	class directCallVisitor : public genericVisitor<F, GroupType, glslHeaderVisitor<F, GroupType>> {
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
		template <typename T>
		std::string literalFor(const T& payload) {
			return std::visit([](const auto& arg) {return glslLiteral(arg); }, payload);
		}
		
	public:
		void visitUp(const typename GroupType::Shape& node) {
		}
		void visitDown(const typename GroupType::Shape& node) {
			
		}

		void visitUp(const typename GroupType::UnaryOp& node) {
		}
		void visitDown(const typename GroupType::UnaryOp& node) {
		}

		void visitUp(const typename GroupType::DomainOp& node) {
		}
		void visitDown(const typename GroupType::DomainOp& node) {
		}

		void visitUp(const typename GroupType::BinaryOp& node) {
		}
		void visitDown(const typename GroupType::BinaryOp& node) {
			
		}
	};
};