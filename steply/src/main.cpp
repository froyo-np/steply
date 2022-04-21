
#include <Windows.h>
#include <gl/GL.h>

/// IM gui
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_opengl3.h>
/// 
#include <thread>
#include <fstream>
#include <iostream>

import imvec;
import distanceVisitor;
import imguiVisitor;
import sdflib;
import sdfNode;

using namespace SDF;

using sdfNode = sdfTreeGroup<binOpVariant<float>, unaryOpVariant<float>, domainOpVariant<float>, shapeVariant<float>>;
using sdflib = SDFLIB<float, sdfNode>;


#define WINDOWMODE WS_VISIBLE | WS_OVERLAPPEDWINDOW

#define MAX_LOADSTRING 100
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
float frand()
{
	unsigned int x = rand() % 100000;
	return (float)x / 100000.0f;
}

#define APPNAME L"SDF VIEWER"
ATOM MyRegisterClass(HINSTANCE hInstance)
{

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(107));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(109);
	wcex.lpszClassName = APPNAME;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(108));

	return RegisterClassExW(&wcex);
}
int main()
{
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	WNDCLASS wc;
	HWND hWnd;
	LPCWSTR lpszAppName = APPNAME;
	if (!MyRegisterClass(hInstance))
	{
		std::cout << "register failed " << GetLastError() << std::endl;
	}
	HWND desktop;
	HDC desktopdc;
	DWORD winError;
	int screenx, screeny;
	desktop = GetDesktopWindow();
	desktopdc = GetDC(desktop);
	screenx = GetDeviceCaps(desktopdc, HORZRES);
	screeny = GetDeviceCaps(desktopdc, VERTRES);
	ReleaseDC(desktop, desktopdc);

	hWnd =
		CreateWindowEx(WS_EX_APPWINDOW, lpszAppName, lpszAppName, WINDOWMODE, 0,
			0, screenx, screeny, nullptr, nullptr, hInstance, nullptr);
	MSG msg;
	BOOL bRet;
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
	while ((bRet = GetMessage(&msg, hWnd, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	};
}
PIXELFORMATDESCRIPTOR getPreferredPixelFormatDescriptor()
{

	PIXELFORMATDESCRIPTOR pfd;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 32;
	pfd.cStencilBits = 8; // need stencil buffer for eraser and user masking
	pfd.cAccumBits = 0;
	pfd.cAccumRedBits = 8;
	pfd.cAccumBlueBits = 8;
	pfd.cAccumGreenBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;
	return pfd;
}

// what is this magic?
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	using namespace ivec;
	using uivec2 = ivec::vec<unsigned int, 2>;
	using fvec3 = ivec::vec<float, 3>;
	using ivec2 = ivec::vec<int, 2>;
	static HDC hdc;
	static HGLRC hglRC;
	static int screenWidth;
	static int screenHeight;
	// mouse garbage: delete me please!
	static ivec2 lastMousePosScreenPx(0,0);
	static bool lDown = false;
	static bool rDown = false;
	static float camDistance = -12;
	static fvec3 camPoint(0, 0, camDistance);
	static float frametime = 0.0;
	static mat<float, 4> mdl;
	static std::string clipboard;
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
	{
		return true;
	}
	switch (message)
	{
	case WM_SIZE:
	{
		screenWidth = LOWORD(lParam);
		screenHeight = HIWORD(lParam);
	}
	break;
	case WM_KEYUP:
	{
		
	}
	case WM_CREATE:
	{

		hdc = GetWindowDC(hWnd);
		// setup pixel format request
		PIXELFORMATDESCRIPTOR pfd = getPreferredPixelFormatDescriptor();
		int pixform = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, pixform, &pfd);
		/**
		int attribs[] = { WGL_CONTEXT_MAJOR_VERSION_ARB, 3, WGL_CONTEXT_MINOR_VERSION_ARB, 3, WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, 0, 0 };
		HGLRC hRC = OGL::getContext(hdc, attribs);
		if (hRC) {
			if (!OGL::bind(hdc)) {
				// this set of required extensions failed - load a different fallback set?
				// TODO
				// for now, just die
				std::cerr << " warning! failed to bind required extensions! crash is now!" << std::endl;
				PostQuitMessage(0);
			}
		}
		else {
			// no context available?
			std::cerr << " warning! failed to acquire OGL context! crash is now!" << std::endl;
			PostQuitMessage(0);
		}
		std::cout << "GL initialization complete..." << std::endl;
		const GLubyte* str = OGL::GetString(GL_VERSION);
		std::cout << "OGL reports version: " << str << std::endl;

		// IM GUI //
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplOpenGL3_Init("#version 130");
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		*/
	}
	break;
	case WM_MOUSEWHEEL:
	{
		auto delta = GET_WHEEL_DELTA_WPARAM(wParam);
		camDistance += ((float)delta) / 220.0f;
		camPoint = fvec3(camPoint.xy(), camDistance);
	}
	break;
	case WM_MOUSEMOVE:
	{
		int mousey = screenHeight - HIWORD(lParam);
		int mousex = LOWORD(lParam);
		ivec2 mousePosPx(mousex, mousey);
		if (rDown) {
			// do the arc-ball thing! how did that go again?
			ivec2 mdelta(mousePosPx - lastMousePosScreenPx);
			if (mdelta.x() != 0 || mdelta.y() != 0) {
				float rx = mdelta.x() / 120.0;
				float ry = mdelta.y() / 120.0;
				mdl = rotateAboutAxis4<float>(vec<float, 3>(1, 0, 0), -ry) * mdl;
				mdl = rotateAboutAxis4<float>(vec<float, 3>(0, 1, 0), rx) * mdl;
			}

		}
		lastMousePosScreenPx = mousePosPx;
	}
	break;
	case WM_LBUTTONDOWN:
		if (!lDown)
		{
		}
		lDown = true;
		break;
	case WM_LBUTTONUP:
		if (lDown)
		{
		}
		lDown = false;
		break;
	case WM_RBUTTONDOWN:
		rDown = true;
		break;
	case WM_RBUTTONUP:
		rDown = false;

		break;
	case WM_PAINT:
	{
		// IMGUI //
		if (false) { // TODO
			//ImGui_ImplOpenGL3_NewFrame();
			//ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			// draw the gui
			
			ImGui::Render();
			//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}


		SwapBuffers(hdc);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}

