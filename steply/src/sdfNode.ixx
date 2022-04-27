module;
#include <vector>
#include <variant>
#include <array>
#include <iostream>
export module sdfNode;
import AbstractNode;

namespace SDF {

	template <typename V>
	using Vlst = std::array<V, std::variant_size_v<V>>;

	template <typename V>
	constexpr Vlst<V> makeAll()
	{
		Vlst<V> lst;
		makeRest<V>(lst);
		return lst;
	}
	template <typename V, std::size_t I = std::variant_size_v<V>-1>
	constexpr void makeRest(Vlst<V>& lst) {
		if constexpr (I >= 0) {
			lst[I] = std::variant_alternative_t<I,V>();
		}
		if constexpr (I > 0) {
			makeRest<V, I - 1>(lst);
		}
	}
	export template <class P, class GroupType>
		class BinOp : public Nodes::Node<P> {
		protected:
			std::vector<typename GroupType::NodeVariant> children;
		public:
			inline const typename GroupType::NodeVariant& getLhs() const { return children[0]; }
			inline const typename GroupType::NodeVariant& getRhs() const { return children[1]; }
			inline typename GroupType::NodeVariant& getLhs() { return children[0]; }
			inline typename GroupType::NodeVariant& getRhs() { return children[1]; }
			// puts the node in an invalid state... TODO
			inline typename GroupType::NodeVariant&& takeLhs() { return std::move(children[0]); }
			inline typename GroupType::NodeVariant&& takeRhs() { return std::move(children[1]); }
			inline void setLhs(typename GroupType::NodeVariant&& node) {
				children[0] = std::move(node);
			}

			inline void setRhs(typename GroupType::NodeVariant&& node) {
				children[1] = std::move(node);
			}
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
			inline typename GroupType::NodeVariant& getChild() { return child[0]; }
			inline typename GroupType::NodeVariant&& takeChild() { return std::move(child[0]); }
			inline void setChild(typename GroupType::NodeVariant&& node) {
				child[0] = std::move(node);
			}
			
	};
	export template <class P, class GroupType>
		class DomOp : public Nodes::Node<P> {
		protected:
			std::vector<typename GroupType::NodeVariant> child;
		public:
			template <typename V>
			explicit DomOp(V&& v, typename GroupType::NodeVariant&& subTree) : Nodes::Node<P>(std::move(v)), child({ subTree }) {}
			inline const typename GroupType::NodeVariant& getChild() const { return child[0]; }
			inline typename GroupType::NodeVariant& getChild() { return child[0]; }
			inline typename GroupType::NodeVariant&& takeChild() { return std::move(child[0]); }
			inline void setChild(typename GroupType::NodeVariant&& node) {
				child[0] = std::move(node);
			}
			
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
			
			template <typename T>
			constexpr static unsigned int getVariantListSize() {
				return std::variant_size_v<T>;
			}
			template <typename T>
			static Vlst<T> getDefaultVariantList() {
				static Vlst<T> lst = makeAll<T>();
				return lst;
			}
	};
}