#include "OGL.h"

PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB = nullptr;

HGLRC getContext(HDC hdc, int attribs[]) {
	HGLRC hglRC = wglCreateContext(hdc);
	// we use a dummy context to get wglCreateContextAttribsARB - then we use that to build a 
	// context to our liking. if that works, wer return it after deleting the dummy context
	wglMakeCurrent(hdc, hglRC);
	// make it current
	OPENGL_REQUIRED_GETPROCADDRESS(PFNWGLCREATECONTEXTATTRIBSARBPROC, wglCreateContextAttribsARB);
	if (wglCreateContextAttribsARB == nullptr) {
		return nullptr;
	}
	HGLRC hRC = wglCreateContextAttribsARB(hdc, 0, attribs);
	if (hRC != nullptr) {
		wglMakeCurrent(hdc, nullptr);		//no current context, safe to delete old.
		wglDeleteContext(hglRC);
		wglMakeCurrent(hdc, hRC);
		hglRC = hRC;

		OPENGL_REQUIRED_GETPROCADDRESS(PFNWGLGETEXTENSIONSSTRINGARBPROC, wglGetExtensionsStringARB);
		bool success = wglGetExtensionsStringARB != nullptr;
		return success ? hRC : nullptr;
	}
	return nullptr;
}

bool bindRequiredExtensions(HDC hdc) {
	bool success = wglGetExtensionsStringARB != nullptr;
	const char* allExt = wglGetExtensionsStringARB(hdc);
	// bind all the others!
	// TODO we are going to need a bunch of these
	_gl::bindGL_VERSION_2_0(allExt);
	_gl::bindGL_VERSION_3_0(allExt);
	return success;
}

HGLRC CreateContextAttribs(HDC hDC, HGLRC glRC, const int* attrs) {
	return wglCreateContextAttribsARB(hDC, glRC, attrs);
}
