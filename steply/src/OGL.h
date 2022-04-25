#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include "wglext.h"
#include "glext.h"
#define OPENGL_REQUIRED_GETPROCADDRESS(type, func) \
	func = (type)wglGetProcAddress(#func);

HGLRC getContext(HDC hdc, int attribs[]);

bool bindRequiredExtensions(HDC hdc);
HGLRC CreateContextAttribs(HDC hDC, HGLRC glRC, const int* attrs);