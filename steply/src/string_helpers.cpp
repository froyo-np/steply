#include "string_helpers.h"

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
std::string print(float f) {
	std::stringstream ss;
	ss << f;
	return ss.str();
}

std::string print(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}

std::string print(unsigned int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}
