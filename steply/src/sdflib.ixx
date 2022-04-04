module;
#include <memory>
#include <variant>
#include <vector>
export module sdflib;
import imvec;
import AbstractNode;

// prims
export import sdfBox;
export import sdfCone;
export import sdfSphere;
export import sdfTorus;

// ops
export import sdfIntersect;
export import sdfSubtract;
export import sdfUnion;
export import round;
export import move;

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
	

	// although it is tempting to remove binOpHolder as a type, 
	// its not as nice as it seems, since we have to store it in binOp
	// to do that, we would put a requires<P> | (binOpFn(P, a, b) exists
	// but then binOp would still need to be templated on Type P, as it is now
	// the variant lets us remove the P, at the cost of the fact that we have to update
	// the binOpHelper 'type' every time we add a new binop. hmmm.
	export template <typename F>
	using binOpVariant = std::variant<union_sdf<F>, smoothUnion<F>, intersect<F>, smoothIntersect<F>, subtract<F>, smoothSubtract<F>>;

	export template <typename F>
	using unaryOpVariant = std::variant<round<F>>;

	export template <typename F>
	using domainOpVariant = std::variant<move<F>>;
	
	export template <typename F>
	using primOpVariant = std::variant<cone<F>, box<F>, torus<F>, sphere<F>>;
	
	template <typename F>
	class BinOp;
	template <typename F>
	class UnaryOp;
	template <typename F>
	class DomainOp;

	export template <typename F>
	using NodeVariants = std::variant<BinOp<F>, UnaryOp<F>, DomainOp<F>>;
	
	export template <typename F>
	using LeafOrNode = std::variant<NodeVariants<F>, primOpVariant<F>>;

	export template <typename F>
	class BinOp : public AbsNode<binOpVariant<F>, NodeVariants<F>, primOpVariant<F>> {
	public:
		BinOp(binOpVariant<F>&& op, LeafOrNode<F>&& lhs, LeafOrNode<F>&& rhs) : AbsNode<binOpVariant<F>, NodeVariants<F>, primOpVariant<F>>(std::move(op), { std::move(lhs),std::move(rhs) }) {}
		inline const LeafOrNode<F>& getLhs() const { return this->children[0]; }
		inline const LeafOrNode<F>& getRhs() const { return this->children[1]; }
	};

	export template <typename F>
	class UnaryOp : public AbsNode<unaryOpVariant<F>,NodeVariants<F>, primOpVariant<F>> {
	public:
		UnaryOp(unaryOpVariant<F>&& op, LeafOrNode<F>&& tree) : AbsNode<unaryOpVariant<F>, NodeVariants<F>, primOpVariant<F>>(std::move(op), { std::move(tree) }) {}
		inline const LeafOrNode<F>& getChild() const { return this->children[0]; }
	};
	export template <typename F>
	class DomainOp : public AbsNode<domainOpVariant<F>, NodeVariants<F>, primOpVariant<F>> {
	public:
		DomainOp(domainOpVariant<F>&& op, LeafOrNode<F>&& tree) : AbsNode<domainOpVariant<F>, NodeVariants<F>, primOpVariant<F>>(std::move(op), { std::move(tree) }) {}
		inline const LeafOrNode<F>& getChild() const { return this->children[0]; }
	};


	export template <typename F>
	class sdfLib {
	public:
		
		inline BinOp<F> join(binOpVariant<F>&& op, LeafOrNode<F>&& lhs, LeafOrNode<F>&& rhs) {
			// c++17 copy elision - aka its safe to return like this
			return BinOp<F>(std::move(op), std::move(lhs), std::move(rhs));
		}
		inline UnaryOp<F> modify(unaryOpVariant<F>&& op, LeafOrNode<F>&& subTree) {
			// c++17 copy elision - aka its safe to return like this
			return UnaryOp<F>(std::move(op), std::move(subTree));
		}
		inline DomainOp<F> transform(domainOpVariant<F>&& op, LeafOrNode<F>&& subTree) {
			// c++17 copy elision - aka its safe to return like this
			return DomainOp<F>(std::move(op), std::move(subTree));
		}
		
	};
	
};
