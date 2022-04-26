module;
#include <variant>
#include <iostream>
#include <imgui.h>
export module imguiVisitor;
import imvec;
import sdfNode;
import sdflib;

namespace SDF {
	
	template <typename F, unsigned short N>
	using vec = ivec::vec<F,N>;
	template <typename F>
	using prims = shapeVariant<F>;
	
	// annoyance 1. since we want a combo box with every possible type of node available for picking,
	// we must import ALL node types - this is made easy, just import sdflib.
	template <typename GroupType, typename NodeType, typename VType>
	void payloadTypeChanger(NodeType& node) {
		int index = node.getPayload().index();

		auto wtf = GroupType::template getDefaultVariantList<VType>();
		constexpr unsigned int N = GroupType::template getVariantListSize<VType>();

		const char* lbls[N];
		for (unsigned int i = 0; i < N; ++i) {
			lbls[i] = std::visit([](const auto& arg) {return uiName(arg); }, wtf[i]);
		}
		if (ImGui::Combo("type", &index, lbls, N)) {
			// replace my payload...?
			auto copy = wtf[index];
			node.setPayload(copy);
		}
	}

	// TODO if the type used for F is not float.. this whole GUI will probably fail to compile problem
	inline vec<float, 3> Edit(const char* lbl, vec<float, 3> v, bool* changed) {
		float xyz[3];
		xyz[0] = v.x();
		xyz[1] = v.y();
		xyz[2] = v.z();
		if (ImGui::DragFloat3(lbl, xyz, 0.001)) {
			*changed = true;
			return vec<float, 3>(xyz);
		}
		return v;
	}
	inline vec<float, 3> EditPositive(const char* lbl, vec<float, 3> v, bool* changed) {
		float xyz[3];
		xyz[0] = v.x();
		xyz[1] = v.y();
		xyz[2] = v.z();
		if (ImGui::DragFloat3(lbl, xyz, 0.001, 0.0)) {
			*changed = true;
			return vec<float, 3>(xyz);
		}
		return v;
	}

	inline float Edit(const char* lbl, float v, bool* changed) {
		if (ImGui::DragFloat(lbl, &v, 0.001)) {
			*changed = true;
		}
		return v;
	}
	inline float EditPositive(const char* lbl, float v, bool* changed) {
		if (ImGui::DragFloat(lbl, &v, 0.001, 0.0)) {
			*changed = true;
		}
		return v;
	}
	//
	template <typename F>
	box<F> Edit(const box<F>& obj, bool* changed) {
		auto size = EditPositive("size", obj.dim, changed);
		if (changed) {
			return { size };
		}
		return obj;
	}
	template <typename F>
	capsule<F> Edit(const capsule<F>& obj, bool* changed) {
		auto a = Edit("a", obj.a, changed);
		auto b = Edit("b", obj.b, changed);
		auto r = Edit("r", obj.radius, changed);
		if (changed) {
			return capsule<F>{a, b, r};
		}
		return obj;
	}
	template <typename F>
	cylinder<F> Edit(const cylinder<F>& obj, bool* changed) {
		auto r = EditPositive("radius", obj.radius, changed);
		auto h = EditPositive("height", obj.height, changed);
		if (changed) {
			return { r,h };
		}
		return obj;
	}
	template <typename F>
	hexPrism<F> Edit(const hexPrism<F>& obj, bool* changed) {
		auto r = EditPositive("radius", obj.radius, changed);
		auto h = EditPositive("height", obj.height, changed);
		if (changed) {
			return { r,h };
		}
		return obj;
	}
	template <typename F>
	torus<F> Edit(const torus<F>& obj, bool* changed) {
		auto radius = EditPositive("radius", obj.radius, changed);
		auto thickness = EditPositive("thickness", obj.thickness, changed);
		if (changed) {
			return { radius, thickness };
		}
		return obj;
	}

	template <typename F>
	sphere<F> Edit(const sphere<F>& obj, bool* changed) {
		auto size = EditPositive("radius", obj.radius, changed);
		if (changed) {
			return { size };
		}
		return obj;
	}
	template <typename F>
	move<F> Edit(const move<F>& obj, bool* changed) {
		auto pos = Edit("offset", obj.offset, changed);
		if (changed) {
			return { pos };
		}
		return obj;
	}
	template <typename F>
	repeat<F> Edit(const repeat<F>& obj, bool* changed) {
		auto reps = EditPositive("steps", obj.reps, changed);
		auto size = EditPositive("step size", obj.stepSize, changed);
		if (changed) {
			return { reps, size };
		}
		return obj;
	}
	template <typename F>
	round<F> Edit(const round<F>& obj, bool* changed) {
		auto r = EditPositive("radius", obj.radius, changed);
		if (changed) {
			return { r };
		}
		return obj;
	}
	template <typename F>
	subtract<F> Edit(const subtract<F>& obj, bool* changed) {
		return obj;
	}
	template <typename F>
	smoothSubtract<F> Edit(const smoothSubtract<F>& obj, bool* changed) {
		auto r = EditPositive("radius", obj.radius, changed);
		if (changed) {
			return { r };
		}
		return obj;
	}
	template <typename F>
	union_sdf<F> Edit(const union_sdf<F>& obj, bool* changed) {
		return obj;
	}
	template <typename F>
	smoothUnion<F> Edit(const smoothUnion<F>& obj, bool* changed) {
		auto r = EditPositive("radius", obj.radius, changed);
		if (changed) {
			return { r };
		}
		return obj;
	}

	template <typename F>
	intersect<F> Edit(const intersect<F>& obj, bool* changed) {
		return obj;
	}
	template <typename F>
	smoothIntersect<F> Edit(const smoothIntersect<F>& obj, bool* changed) {
		auto r = EditPositive("radius", obj.radius, changed);
		if (changed) {
			return { r };
		}
		return obj;
	}

	template <typename F>
	cone<F> Edit(const cone<F>& obj, bool* changed) {
		auto r = EditPositive("radius", obj.radius, changed);
		auto h = EditPositive("height", obj.height, changed);
		if (changed) {
			return { r,h };
		}
		return obj;
	}

	
	template <typename F, typename N>
	void editPayload(N& node) {
		std::visit([&node](const auto& arg) {
			bool changed = false;
			auto p = Edit<F>(arg, &changed);
			if (changed) {
				node.setPayload(p);
			}
		}, node.getPayload());
	}



	template <typename GroupType>
	using guiResult = std::variant<bool, typename GroupType::NodeVariant>;
	template <typename GroupType>
	guiResult<GroupType> handleVisitResult(typename GroupType::UnaryOp& parent, guiResult<GroupType>& childResult) {
		auto bPtr = std::get_if<bool>(&childResult);
		auto nPtr = std::get_if<typename GroupType::NodeVariant>(&childResult);
		if (bPtr!=nullptr) {
			bool b = *bPtr;
			if (b) {
				// our child was deleted - delete ourselves
				return true;
			}
		}
		else if (nPtr != nullptr) {
			parent.setChild(*nPtr);
		}
		return false;
	}
	template <typename GroupType>
	guiResult<GroupType> handleVisitResult(typename GroupType::DomainOp& parent, guiResult<GroupType>& childResult) {
		auto bPtr = std::get_if<bool>(&childResult);
		auto nPtr = std::get_if<typename GroupType::NodeVariant>(&childResult);
		if (bPtr != nullptr) {
			bool b = *bPtr;
			if (b) {
				// our child was deleted - delete ourselves
				return true;
			}
		}
		else if (nPtr != nullptr) {
			parent.setChild(*nPtr);
		}
		return false;
	}
	template <typename GroupType>
	guiResult<GroupType> handleVisitResult(typename GroupType::BinaryOp& parent, guiResult<GroupType>& lhsResult, guiResult<GroupType>& rhsResult) {
		auto lbPtr = std::get_if<bool>(&lhsResult);
		auto lnPtr = std::get_if<typename GroupType::NodeVariant>(&lhsResult);

		auto rbPtr = std::get_if<bool>(&rhsResult);
		auto rnPtr = std::get_if<typename GroupType::NodeVariant>(&rhsResult);

		if (lbPtr != nullptr) {
			bool b = *lbPtr;
			if (b) {
				return parent.getRhs();
			}
		}
		else if (lnPtr != nullptr) {
			parent.setLhs(*lnPtr);
		}
		// now handle RHS
		if (rbPtr != nullptr) {
			bool b = *rbPtr;
			if (b) {
				return parent.getLhs();
			}
		}
		else if (rnPtr != nullptr) {
			parent.setRhs(*rnPtr);
		}
		return false;
	}


	template<typename F, typename GroupType>
	guiResult<GroupType> guiVisit(typename GroupType::NodeVariant& node);
	
	template<typename F, typename GroupType>
	guiResult<GroupType> guiVisit(typename GroupType::Shape& node);
	
	template<typename F, typename GroupType>
	guiResult<GroupType> guiVisit(typename GroupType::DomainOp& node);
	
	template<typename F, typename GroupType>
	guiResult<GroupType> guiVisit(typename GroupType::UnaryOp& node);
	
	template<typename F, typename GroupType>
	guiResult<GroupType> guiVisit(typename GroupType::BinaryOp& node);

	export template<typename F, typename GroupType>
	guiResult<GroupType> guiVisit(typename GroupType::BinaryOp& node) {
		if (ImGui::SmallButton("x")) {
			return true;
		}
		ImGui::SameLine();
		const char* name = std::visit(
			[](const auto& arg) {return uiName<F>(arg); }, node.getPayload());
		if (ImGui::TreeNode(name)) {
			// show the combo box to change teh type
			payloadTypeChanger<GroupType, typename GroupType::BinaryOp, typename GroupType::binVaraints>(node);
			// show the widget to edit the numeric data of this shape:
			editPayload<F, typename GroupType::BinaryOp>(node);
			// visit child(ren)
			auto lhsResult = guiVisit<F, GroupType>(node.getLhs());
			auto rhsResult = guiVisit<F, GroupType>(node.getRhs());
			ImGui::TreePop();
			return handleVisitResult<GroupType>(node, lhsResult,rhsResult);
		}
		return false;
	}
	export template<typename F, typename GroupType>
	guiResult<GroupType> guiVisit(typename GroupType::UnaryOp& node) {
		if (ImGui::SmallButton("x")) {
			return node.getChild();
		}
		ImGui::SameLine();
		const char* name = std::visit(
			[](const auto& arg) {return uiName<F>(arg); }, node.getPayload());
		if (ImGui::TreeNode(name)) {
			// show the combo box to change teh type
			payloadTypeChanger<GroupType, typename GroupType::UnaryOp, typename GroupType::unaryVariants>(node);
			// show the widget to edit the numeric data of this shape:
			editPayload<F, typename GroupType::UnaryOp>(node);
			// visit child(ren)
			auto result = guiVisit<F, GroupType>(node.getChild());
			ImGui::TreePop();
			return handleVisitResult<GroupType>(node, result);
		}
	}
	export template<typename F, typename GroupType>
	guiResult<GroupType> guiVisit(typename GroupType::DomainOp& node) {
		if (ImGui::SmallButton("x")) {
			return node.getChild();
		}
		ImGui::SameLine();
		const char* name = std::visit(
			[](const auto& arg) {return uiName<F>(arg); }, node.getPayload());
		if (ImGui::TreeNode(name)) {
			// show the combo box to change teh type
			payloadTypeChanger<GroupType, typename GroupType::DomainOp, typename GroupType::domainVariants>(node);
			// show the widget to edit the numeric data of this shape:
			editPayload<F, typename GroupType::DomainOp>(node);
			// visit child(ren)
			auto result = guiVisit<F, GroupType>(node.getChild());
			ImGui::TreePop();
			return handleVisitResult<GroupType>(node, result);
		}
	}
	export template<typename F, typename GroupType>
	guiResult<GroupType> guiVisit(typename GroupType::Shape& node) {
		if (ImGui::SmallButton("x")) {
			return true;
		}
		ImGui::SameLine();
		const char* name = std::visit(
			[](const auto& arg) {return uiName<F>(arg); }, node.getPayload());
		if (ImGui::TreeNode(name)) {
			// show the combo box to change teh type
			payloadTypeChanger<GroupType, typename GroupType::Shape, typename GroupType::leafVariants>(node);
			// show the widget to edit the numeric data of this shape:
			editPayload<F, typename GroupType::Shape>(node);
			ImGui::TreePop();
		}
	}

	export template<typename F, typename GroupType>
	guiResult<GroupType> guiVisit(typename GroupType::NodeVariant& node) {
		return std::visit(
			[](auto& arg) {return guiVisit<F, GroupType>(arg); }, node);
	}
};