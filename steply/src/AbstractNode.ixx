module;
#include <vector>
#include <variant>

export module AbstractNode;

namespace Nodes {
	/**
	template <class P, class N, class L>
	class AbsNode {
		using childType = std::variant<N, L>;
	protected:
		P payload;
		std::vector<childType> children;
		explicit AbsNode(P&& p, std::initializer_list<childType> subtrees) : payload(std::move(p)), children(subtrees) {}
	public:
		inline const P& getPayload() const { return payload; }
		inline auto getChildItr() const { return children.cbegin(); }
		inline auto getChildEnd() const { return children.cend(); }
	};
	export template <typename F, class B, class U, class D, class L>
	class _SDFLIB {

	public:
		class BinOp;
		class UnaryOp;
		class DomainOp;

		using NodeVariants = std::variant<BinOp, UnaryOp, DomainOp>;

		using LeafOrNode = std::variant<NodeVariants, L>;

		class BinOp : public AbsNode<B, NodeVariants, L> {
		public:
			BinOp(B&& op, LeafOrNode&& lhs, LeafOrNode&& rhs) : AbsNode<B, NodeVariants, L>(std::move(op), { std::move(lhs),std::move(rhs) }) {}
			inline const LeafOrNode& getLhs() const { return this->children[0]; }
			inline const LeafOrNode& getRhs() const { return this->children[1]; }
		};

		class UnaryOp : public AbsNode<U, NodeVariants, L> {
		public:
			UnaryOp(U&& op, LeafOrNode&& tree) : AbsNode<U, NodeVariants, L>(std::move(op), { std::move(tree) }) {}
			inline const LeafOrNode& getChild() const { return this->children[0]; }
		};
		class DomainOp : public AbsNode<D, NodeVariants, L> {
		public:
			DomainOp(D&& op, LeafOrNode&& tree) : AbsNode<D, NodeVariants, L>(std::move(op), { std::move(tree) }) {}
			inline const LeafOrNode& getChild() const { return this->children[0]; }
		};
	};
	*/

	template <typename N, typename V>
	concept is_visitable = requires(N n, V v) {
		{visit(n, v) };
	};

	export template <class... nodeVariants>
	class StructuredTree {
	protected:
		explicit StructuredTree() = delete;	// non-constructable class...
	public:
		using NodeVariant = std::variant<nodeVariants...>;
		
	};
	export template <class Var>
	class Node {
	protected:
		Var payload;
		template <typename V> // todo require V to be assignable to Var
		Node(V&& v) : payload(std::move(v)) {}
	public:
		inline Var getPayload() const { return payload; }
		// TODO is it possible to make a boilerplate visitor?


	};
};