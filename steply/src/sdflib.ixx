module;
#include <memory>
#include <variant>
#include <vector>
export module sdflib;
import imvec;

// prims
export import sdfBox;
export import sdfCone;
export import sdfSphere;
export import sdfTorus;

// ops
export import sdfIntersect;
export import sdfSubtract;
export import sdfUnion;

namespace SDF {
	// note: we only export the free functions,
	// the Node class, and the helper lib class
	
	// I have a few competing goals
	// 1. it seems like its a good idea to separate the tree-ness
	// from the math-ness. this is however problematic, because a thing that represents a union, or intersection,
	// is only a "sdf shape" IF it can evaluate its children
	// I would like to visit trees of these things - each visitor does a different thing with the data it finds
	// It would be great to add visitors trivially, especially if I could avoid knowing the type of the visitor...
	// the visitor can know the type of the data at a spot in the tree though
	
	// issue - I would need to change this to add a new bin-op type...
	// thats less-nice than an interface pointer...
	// but not really the heaviest burden...

	// although it is tempting to remove binOpHolder as a type, 
	// its not as nice as it seems, since we have to store it in binOp
	// to do that, we would put a requires<P> | (binOpFn(P, a, b) exists
	// but then binOp would still need to be templated on Type P, as it is now
	// the variant lets us remove the P, at the cost of the fact that we have to update
	// the binOpHelper 'type' every time we add a new binop. hmmm.
	template <typename F>
	using binOpVariant = std::variant<union_sdf<F>, smoothUnion<F>, intersect<F>, smoothIntersect<F>, subtract<F>, smoothSubtract<F>>;
	
	template <typename F>
	using primOpVariant = std::variant<cone<F>, box<F>, torus<F>, sphere<F>>;
	
	template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };

	// this is simply the concept-version of 'primOpHolder'
	// TODO: require it return type F... -> F didn't work...
	// TODO: name this 'distanceTo_able' ?
	template <typename P, typename F>
	concept PrimOpAble = requires(P v, ivec::vec<F, 3> pnt) {
		distanceTo(v, pnt);
	};

	// likewise, the conceptual requirement of being able to call sdfBinaryOp on it
	template <typename P, typename F>
	concept BinOpAble = requires(P v, F a, F b) {
		sdfBinaryOp(v, a, b);
	};
	template <class ...Ts> struct VisitorCases : Ts... {using Ts::operator()...; };
	
	export template <typename F>
	struct Node; // forward decl

	template <typename F>
	class binOp {
	private:
		binOpVariant<F> op;
		// because of heap-allocation and allocator-something-something, we can have a container
		// of incomplete types declared!
		std::vector<Node<F>> children;
		friend F distanceTo(const binOp<F>& self, const ivec::vec<F, 3>& p);
	public:
		explicit binOp(binOpVariant<F>&& Op, Node<F>&& lhs, Node<F>&& rhs) : op(Op), children({ std::move(lhs), std::move(rhs) }) {}
	};
	
	template <typename F>
	using NodeClass = std::variant<binOp<F>, primOpVariant<F>>; // TODO add unaryOpVariant, domainOpVariant
	template <typename F>
	struct Node {
		NodeClass<F> payload;
		explicit Node(NodeClass<F>&& data) : payload(std::move(data)) {}
	};

	// arbitrary nodes distance function!
	export template <typename F>
	F distanceTo(const Node<F>& self, const ivec::vec<F, 3>& p) {
		return std::visit( // primOpVariant, binOp
			[&p](const auto& arg) {return distanceTo<F>(arg, p); },
			self.payload
		);
	}
	// the binOp version  - note I am a friend of the class, hence I may touch the insides
	export template <typename F>
	F distanceTo(const binOp<F>& self, const ivec::vec<F, 3>& p) {
		F a = distanceTo<F>(self.children[0], p);
		F b = distanceTo<F>(self.children[1], p);
		return std::visit( // all 6 types of binOp can be deduced!
			[a, b](const auto& arg) {return sdfBinaryOp<F>(arg, a, b); }, self.op);
	}
	// the primitive-op variant distanceTo fn
	export template <typename F>
	F distanceTo(const primOpVariant<F>& prim, const ivec::vec<F,3>& pnt) {
		return std::visit( // obviously, all types of primitive are handled here, and the compiler generates all the versions of this... somehow!
			[&pnt](const auto& unwrapped) {return SDF::distanceTo<F>(unwrapped, pnt); }
		, prim);
	}
	export template <typename P, typename F>
	requires PrimOpAble<P, F>
	F visitDistance(const P& self, const ivec::vec<F, 3>& p) {
		return distanceTo<F>(self, p);
	}

	export template <typename F>
	class sdfLib {
	public:
		inline Node<F> Shape(primOpVariant<F>&& prim) {
			// c++17 copy elision - aka its safe to return like this
			return Node<F>(std::move(prim));
		}
		inline Node<F> BinOp(binOpVariant<F>&& op, Node<F>&& lhs, Node<F>&& rhs) {
			// c++17 copy elision - aka its safe to return like this
			return Node<F>(binOp<F>(std::move(op), std::move(lhs), std::move(rhs)));
		}
		inline Node<F> BinOp(binOpVariant<F>&& op, primOpVariant<F>&& lhs, Node<F>&& rhs) {
			// c++17 copy elision - aka its safe to return like this
			return Node<F>(binOp<F>(std::move(op), Shape(std::move(lhs)), std::move(rhs)));
		}
		inline Node<F> BinOp(binOpVariant<F>&& op, Node<F>&& lhs, primOpVariant<F>&& rhs) {
			// c++17 copy elision - aka its safe to return like this
			return Node<F>(binOp<F>(std::move(op), std::move(lhs), Shape(std::move(rhs))));
		}
		inline Node<F> BinOp(binOpVariant<F>&& op, primOpVariant<F>&& lhs, primOpVariant<F>&& rhs) {
			// c++17 copy elision - aka its safe to return like this
			return Node<F>(binOp<F>(std::move(op), Shape(std::move(lhs)), Shape(std::move(rhs))));
		}
	};
	
};
