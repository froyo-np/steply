module;
#include <variant>
#include <iostream>
#include <imgui.h>
export module imguiVisitor;
import imvec;
import sdfNode;
import AbstractEditor;
namespace SDF {
	
	template <typename F, unsigned short N>
	using vec = ivec::vec<F,N>;

	// TODO if the type used for F is not float.. this whole GUI will probably fail to compile problem
	class ImGuiEditor : public IEditor<float>
	{
	public:
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
	};
	template <typename F, typename N>
	void editPayload(N& node) {
		std::visit([&node](const auto& arg) {
			ImGuiEditor editor;
			bool changed = false;
			auto p = Edit<F>(arg, &editor, &changed);
			if (changed) {
				node.setPayload(p);
			}
		}, node.getPayload());
	}
	

	template<typename F, typename GroupType>
	void guiVisit(typename GroupType::NodeVariant& node);
	
	template<typename F, typename GroupType>
	void guiVisit(typename GroupType::Shape& node);
	
	template<typename F, typename GroupType>
	void guiVisit(typename GroupType::DomainOp& node);
	
	template<typename F, typename GroupType>
	void guiVisit(typename GroupType::UnaryOp& node);
	
	template<typename F, typename GroupType>
	void guiVisit(typename GroupType::BinaryOp& node);

	export template<typename F, typename GroupType>
	void guiVisit(typename GroupType::BinaryOp& node) {
		const char* name = std::visit(
			[](const auto& arg) {return uiName<F>(arg); }, node.getPayload());
		if (ImGui::TreeNode(name)) {
			// show the widget to edit the numeric data of this shape:
			editPayload<F, typename GroupType::BinaryOp>(node);
			// visit child(ren)
			guiVisit<F, GroupType>(node.getLhs());
			guiVisit<F, GroupType>(node.getRhs());
			ImGui::TreePop();
		}
	}
	export template<typename F, typename GroupType>
	void guiVisit(typename GroupType::UnaryOp& node) {
		const char* name = std::visit(
			[](const auto& arg) {return uiName<F>(arg); }, node.getPayload());
		if (ImGui::TreeNode(name)) {
			// show the widget to edit the numeric data of this shape:
			editPayload<F, typename GroupType::UnaryOp>(node);
			// visit child(ren)
			guiVisit<F, GroupType>(node.getChild());
			ImGui::TreePop();
		}
	}
	export template<typename F, typename GroupType>
	void guiVisit(typename GroupType::DomainOp& node) {
		const char* name = std::visit(
			[](const auto& arg) {return uiName<F>(arg); }, node.getPayload());
		if (ImGui::TreeNode(name)) {
			// show the widget to edit the numeric data of this shape:
			editPayload<F, typename GroupType::DomainOp>(node);
			// visit child(ren)
			guiVisit<F, GroupType>(node.getChild());
			ImGui::TreePop();
		}
	}
	export template<typename F, typename GroupType>
	void guiVisit(typename GroupType::Shape& node) {
		const char* name = std::visit(
			[](const auto& arg) {return uiName<F>(arg); }, node.getPayload());
		if (ImGui::TreeNode(name)) {
			// show the widget to edit the numeric data of this shape:
			editPayload<F, typename GroupType::Shape>(node);
			ImGui::TreePop();
		}
	}

	export template<typename F, typename GroupType>
	void guiVisit(typename GroupType::NodeVariant& node) {
		return std::visit(
			[](auto& arg) {return guiVisit<F, GroupType>(arg); }, node);
	}
};