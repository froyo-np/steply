module;
#include <variant>
#include <imgui.h>
export module imguiVisitor;
import imvec;
import sdfNode;

namespace SDF {
	
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
		if (ImGui::TreeNode("bin")) {
			guiVisit<F, GroupType>(node.getLhs());
			guiVisit<F, GroupType>(node.getRhs());
			ImGui::TreePop();
		}
	}
	export template<typename F, typename GroupType>
	void guiVisit(typename GroupType::UnaryOp& node) {
		if (ImGui::TreeNode("un")) {
			guiVisit<F, GroupType>(node.getChild());
			ImGui::TreePop();
		}
	}
	export template<typename F, typename GroupType>
	void guiVisit(typename GroupType::DomainOp& node) {
		if (ImGui::TreeNode("dom")) {
			guiVisit<F, GroupType>(node.getChild());
			ImGui::TreePop();
		}
	}
	export template<typename F, typename GroupType>
	void guiVisit(typename GroupType::Shape& node) {
		if (ImGui::TreeNode("shape")) {
			ImGui::TreePop();
		}
	}

	export template<typename F, typename GroupType>
	void guiVisit(typename GroupType::NodeVariant& node) {
		return std::visit(
			[](auto& arg) {return guiVisit<F, GroupType>(arg); }, node);
	}
};