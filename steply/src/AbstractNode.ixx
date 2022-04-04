module;
#include <vector>
#include <variant>

export module AbstractNode;

export template <class P, class N, class L>
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
