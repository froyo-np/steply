
export module AbstractEditor;
import imvec;
export namespace SDF {
	template <typename F>
	class IEditor {

	public:

		virtual ivec::vec<F, 3> Edit(const char* lbl, ivec::vec<F, 3> v, bool* changed) = 0;
		virtual ivec::vec<F, 3> EditPositive(const char* lbl, ivec::vec<F, 3> v, bool* changed) = 0;
		virtual F Edit(const char* lbl, F v, bool* changed) = 0;
		virtual F EditPositive(const char* lbl, F v, bool* changed) = 0;
	};
}