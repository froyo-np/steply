module;
// the below .hpp is not "visible" (todo: is this technically true?) from importers, because this is the 
// so-called 'global module fragment'
#include <imvec/imvec.hpp>
#include <imvec/mat.hpp>
// thus, what we are doing here is creating a module wrapper around the vanilla .hpp include
export module imvec;
/**/
export namespace ivec {
	// we are effectivly creating ivec::vec<T,N> which is just
	// an alias of imvec::vec - this seems to work great!
	// it hides all the weird stuff (like namespace _deets and all macros in swizzles.h)
	// from our importer! success!
	template<class T, unsigned short N>
	using vec = imvec::vec<T, N>;

	template<class T, unsigned short N>
	using mat = imvec::mat<T, N>;
	
	using imvec::rotateAboutAxis4;


};

/****/

// the above version would work, and its nice to hide things in namespaces
// we could do the slightly simpler version here though - directly export the using delcaration...
// I think I prefer the namespace after all:
/**
export template<class T, unsigned short N>
using vec = imvec::vec<T, N>;
*/