module;
#include <vector>
#include <variant>

export module AbstractNode;

namespace Nodes {
	

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
		inline void setPayload(Var p) { payload = p; }
		// TODO is it possible to make a boilerplate visitor?


	};
};