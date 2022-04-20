module;
#include <vector>
export module sdfNode;
import AbstractNode;

namespace SDF {
	export template <class P, class GroupType>
		class BinOp : public Nodes::Node<P> {
		protected:
			std::vector<typename GroupType::NodeVariant> children;
		public:
			inline const typename GroupType::NodeVariant& getLhs() const { return children[0]; }
			inline const typename GroupType::NodeVariant& getRhs() const { return children[1]; }
			template <typename V>
			explicit BinOp(V&& v, typename GroupType::NodeVariant&& lhs, typename GroupType::NodeVariant&& rhs) : Nodes::Node<P>(std::move(v)), children({ lhs,rhs }) {}
	};
	export template <class P, class GroupType>
		class UnOp : public Nodes::Node<P> {
		protected:
			std::vector<typename GroupType::NodeVariant> child;
		public:
			template <typename V>
			explicit UnOp(V&& v, typename GroupType::NodeVariant&& subTree) : Nodes::Node<P>(std::move(v)), child({ subTree }) {}
			inline const typename GroupType::NodeVariant& getChild() const { return child[0]; }
	};
	export template <class P, class GroupType>
		class DomOp : public Nodes::Node<P> {
		protected:
			std::vector<typename GroupType::NodeVariant> child;
		public:
			template <typename V>
			explicit DomOp(V&& v, typename GroupType::NodeVariant&& subTree) : Nodes::Node<P>(std::move(v)), child({ subTree }) {}
			inline const typename GroupType::NodeVariant& getChild() const { return child[0]; }
	};
	export template <class P>
		class LeafOp : public Nodes::Node<P> {
		protected:
		public:
			template <typename V>
			explicit LeafOp(V&& v) : Nodes::Node<P>(std::move(v)) {}
	};
	export template <typename B, typename U, typename D, typename L, typename... OtherNodeClasses>
		class sdfTreeGroup : public Nodes::StructuredTree<
		BinOp<B, sdfTreeGroup<B,U,D,L,OtherNodeClasses...>>,
		UnOp<U, sdfTreeGroup<B, U, D, L, OtherNodeClasses...>>, 
		DomOp<D, sdfTreeGroup<B, U, D, L, OtherNodeClasses...>>, 
		LeafOp<L>, 
		OtherNodeClasses...> {
		public:
			// variants of payload, per node-class
			using binVaraints = B;
			using unaryVariants = U;
			using domainVariants = D;
			using leafVariants = L;

			// node-classes
			using BinaryOp = BinOp<B, sdfTreeGroup<B, U, D, L, OtherNodeClasses...>>;
			using UnaryOp= UnOp<U, sdfTreeGroup<B, U, D, L, OtherNodeClasses...>>;
			using DomainOp = DomOp<D, sdfTreeGroup<B, U, D, L, OtherNodeClasses...>>;
			using Shape = LeafOp<L>;
	};
}