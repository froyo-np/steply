#pragma once
#include <Windows.h>
#include <stdio.h>

#include <gl/GL.h>
#include "wglext.h"
#include "glext.h"
#define OPENGL_REQUIRED_GETPROCADDRESS(type, func) \
	func = (type)wglGetProcAddress(#func);
#include "GL_VERSION_2_0.h"
#include "GL_VERSION_3_0.h"
HGLRC getContext(HDC hdc, int attribs[]);

bool bindRequiredExtensions(HDC hdc);
HGLRC CreateContextAttribs(HDC hDC, HGLRC glRC, const int* attrs);



namespace OGL {
	using namespace _gl::VERSION_2_0;
	using namespace _gl::VERSION_3_0;
	inline void checkError(const char* msg) {
		auto err = glGetError();
		auto errStr = "";
		switch (err) {
		case GL_INVALID_ENUM:
			errStr = "Invalid Enum";
			break;
		case GL_INVALID_VALUE:
			errStr = "Invalid Value";
			break;
		case GL_INVALID_OPERATION:
			errStr = "Invalid Op";
			break;
		case GL_INVALID_INDEX:
			errStr = "Invalid Index";
			break;
		}
		if (err != 0) {
			printf("%s :: %i, %s", msg, err, errStr);
		}
	}
};