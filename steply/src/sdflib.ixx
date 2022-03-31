module;
#include <memory>
#include <variant>
#include <vector>
export module sdflib;
import imvec;
export import sdfBox;
export import sdfCone;
export import sdfSphere;
export import sdfTorus;

// ops
export import sdfIntersect;
export import sdfSubtract;
export import sdfUnion;

// so, the concept of a primative is anything where the following free function exists:
// distanceTo(const sdf_primative_type& s, const ivec::vec<F,3>& p) => F

// the concept of a binary SDF operator:
// sdfBinaryOp(const sdf_binary_op_type& self, F a, F b) => F

// we want to compose sdf ops and primitives into trees, and that
// tree should be distanceTo(tree, p) able

// so... having an interface, from which the templated implementation hangs
// is how I've done this before.
// in the type erased world... we should go a step further...
/*
class sdfObj {
private:
class sdfConcept {}
class sdfModel<T> {}
public:
std::unique_ptr<sdfConcept> pImpl;
};

// I'm still struggling with what hiding this in a private class wrapper gets us...
// why not just pass concepts around?
// I guess so we can use a bridge pattern?


*/
export namespace SDF {
	/**
	template <typename F>
	class sdfConcept {
	public:
		// TODO: is this really type erasure? 
		// I dont want to clog this with other junk, UI, tree-traversal, etc...
		// how do I separate those out of the interface...?
		virtual F getDistance(const ivec::vec<F, 3>& p) const = 0;
		virtual ~sdfConcept() = default;
	};
	template <typename P, typename F>
	class sdfPrim : public sdfConcept<F> {
		std::shared_ptr<P> sdf_prim;
	public:
		sdfPrim(P p) : sdf_prim(std::make_shared<P>(p)) {}
		F getDistance(const ivec::vec<F, 3>& p) const override {
			const P& me = *sdf_prim;
			return distanceTo(me, p);
		}
	};

	template <typename P, typename F>
	class sdfBinOp : public sdfConcept<F> {
		std::shared_ptr<P> sdf_self;
		std::shared_ptr<sdfConcept<F>> lhs, rhs;
	public:
		sdfBinOp(P p, std::shared_ptr<sdfConcept<F>> LHS, std::shared_ptr<sdfConcept<F>> RHS) : sdf_self(std::make_shared<P>(p)), lhs(LHS), rhs(RHS) {}
		F getDistance(const ivec::vec<F, 3>& p) const override {
			const P& me = *sdf_self;
			F a = lhs->getDistance(p);
			F b = rhs->getDistance(p);
			return sdfBinaryOp(me, a, b);
		}
	};

	template <typename F>
	class SDFLIB {
	public:
		SDFLIB() = default;
		template <typename Bop>
		std::shared_ptr<sdfConcept<F>> BinOp(const Bop& op, std::shared_ptr<sdfConcept<F>> lhs, std::shared_ptr<sdfConcept<F>> rhs) {
			return std::make_shared<sdfBinOp<Bop, F>>(op, lhs, rhs);
		}
		std::shared_ptr<sdfConcept<F>> Union(std::shared_ptr<sdfConcept<F>> lhs, std::shared_ptr<sdfConcept<F>> rhs) {
			union_sdf<F> fake = {};
			return BinOp(fake, lhs, rhs);
		}
		std::shared_ptr<sdfConcept<F>> Union(const smoothUnion<F>& su, std::shared_ptr<sdfConcept<F>> lhs, std::shared_ptr<sdfConcept<F>> rhs) {
			return BinOp(su, lhs, rhs);
		}
		std::shared_ptr<sdfConcept<F>> Union(F r, std::shared_ptr<sdfConcept<F>> lhs, std::shared_ptr<sdfConcept<F>> rhs) {
			smoothUnion<F>& su(r);
			return BinOp(su, lhs, rhs);
		}

		std::shared_ptr<sdfConcept<F>> Intersect(std::shared_ptr<sdfConcept<F>> lhs, std::shared_ptr<sdfConcept<F>> rhs) {
			intersect<F> fake = {};
			return BinOp(fake, lhs, rhs);
		}
		std::shared_ptr<sdfConcept<F>> Intersect(const smoothIntersect<F>& su, std::shared_ptr<sdfConcept<F>> lhs, std::shared_ptr<sdfConcept<F>> rhs) {
			return BinOp(su, lhs, rhs);
		}
		std::shared_ptr<sdfConcept<F>> Intersect(F r, std::shared_ptr<sdfConcept<F>> lhs, std::shared_ptr<sdfConcept<F>> rhs) {
			smoothIntersect<F>& su(r);
			return BinOp(su, lhs, rhs);
		}

		std::shared_ptr<sdfConcept<F>> Subtract(std::shared_ptr<sdfConcept<F>> lhs, std::shared_ptr<sdfConcept<F>> rhs) {
			subtract<F> fake = {};
			return BinOp(fake, lhs, rhs);
		}
		std::shared_ptr<sdfConcept<F>> Subtract(const smoothSubtract<F>& su, std::shared_ptr<sdfConcept<F>> lhs, std::shared_ptr<sdfConcept<F>> rhs) {
			return BinOp(su, lhs, rhs);
		}
		std::shared_ptr<sdfConcept<F>> Subtract(F r, std::shared_ptr<sdfConcept<F>> lhs, std::shared_ptr<sdfConcept<F>> rhs) {
			smoothSubtract<F>& su(r);
			return BinOp(su, lhs, rhs);
		}
		template <typename P>
		std::shared_ptr<sdfConcept<F>> Prim(const P& p) {
			return std::make_shared<sdfPrim<P, F>>(p);
		}
		std::shared_ptr<sdfConcept<F>> Box(const box<F>& b) {
			return Prim(b);
		}
		std::shared_ptr<sdfConcept<F>> Cone(const cone<F>& c) {
			return Prim(c);
		}
		std::shared_ptr<sdfConcept<F>> Torus(const torus<F>& t) {
			return Prim(t);
		}
		std::shared_ptr<sdfConcept<F>> Sphere(const sphere<F>&s) {
			return Prim(s);
		}
	};
	**/
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
	
	template <typename F>
	struct Node; // forward decl

	template <typename F>
	struct binOp {
		binOpVariant<F> op;
		// because of heap-allocation and allocator-something-something, we can have a container
		// of incomplete types declared!
		std::vector<Node<F>> children;
		explicit binOp(binOpVariant<F>&& Op, Node<F>&& lhs, Node<F>&& rhs) : op(Op), children({ std::move(lhs), std::move(rhs) }) {}
		// friend free function injected into surrounding namespace...
		// thus a binOp should satisfy the PrimOpAble Concept requirement
		friend F distanceTo(const binOp<F>& self, const ivec::vec<F, 3>& p);
	};
	
	template <typename F>
	using NodeClass = std::variant<binOp<F>, primOpVariant<F>>; // TODO add unaryOpVariant, domainOpVariant
	template <typename F>
	struct Node {
		NodeClass<F> payload;
		explicit Node(NodeClass<F>&& data) : payload(std::move(data)) {}
	};

	// arbitrary nodes distance function!
	template <typename F>
	F distanceTo(const Node<F>& self, const ivec::vec<F, 3>& p) {
		return std::visit( // primOpVariant, binOp
			[&p](const auto& arg) {return distanceTo<F>(arg, p); },
			self.payload
		);
	}
	// the binOp version  - note I am a friend of the class, hence I may touch the insides
	template <typename F>
	F distanceTo(const binOp<F>& self, const ivec::vec<F, 3>& p) {
		F a = distanceTo<F>(self.children[0], p);
		F b = distanceTo<F>(self.children[1], p);
		return std::visit( // all 6 types of binOp can be deduced!
			[a, b](const auto& arg) {return sdfBinaryOp<F>(arg, a, b); }, self.op);
	}
	// the primitive-op variant distanceTo fn
	template <typename F>
	F distanceTo(const primOpVariant<F>& prim, const ivec::vec<F,3>& pnt) {
		return std::visit( // obviously, all types of primitive are handled here, and the compiler generates all the versions of this... somehow!
			[&pnt](const auto& unwrapped) {return SDF::distanceTo<F>(unwrapped, pnt); }
		, prim);
	}
	

	template <typename P, typename F>
	requires PrimOpAble<P, F>
	F visitDistance(const P& self, const ivec::vec<F, 3>& p) {
		return std::visit(
			[&p](const auto& arg) { return distanceTo<F>(arg, p); }, self);
	}
};
