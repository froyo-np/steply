#pragma once
#include <string>
#include <sstream>

#include "imvec\imvec.hpp"
#include "imvec\mat.hpp"
/*****
// so... attempting to use stringstream with c++20 experimental modules refuses to compile - with redefinition errors deep in corecrt.h
std::string print(float f) {
	static char buf[1024];
	sprintf_s(buf, "%f", f);
	return std::string(buf);
}
std::string print(int i) {
	static char buf[1024];
	sprintf_s(buf, "%i", i);
	return std::string(buf);
}
std::string print(unsigned int i) {
	static char buf[1024];
	sprintf_s(buf, "%i", i);
	return std::string(buf);
}
***/
std::string print(float f);
std::string print(int i);
std::string print(unsigned int i);
template <typename F, unsigned short N>
inline std::string vecLiteral(imvec::vec<F, N> v) {
	std::string lit = "vec" + print(N) + "(";
	for (unsigned int i = 0; i < N; i++) {
		lit += print(v[i]);
		if (i < N - 1) {
			lit += ", ";
		}
	}
	return lit + ")";
}

template <typename F, unsigned short N>
inline std::string matLiteral(const imvec::mat<F, N>& m) {
	std::string me = "mat" + print(N) + "(";
	for (unsigned int i = 0; i < N; i++) {
		me += vecLiteral<F,N>(m.row(i));
		if (i < N - 1) {
			me += ", ";
		}
	}
	me += ")";
	return me;
}