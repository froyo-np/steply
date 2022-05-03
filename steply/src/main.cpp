
#include <Windows.h>
#include <gl/GL.h>
#include "glext.h"
#include "wglext.h"
#include "OGL.h"
/// IM gui
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_opengl3.h>
/// 
#include <thread>
#include <fstream>
#include <iostream>
#include <variant>

import imvec;
import distanceVisitor;
import imguiVisitor;
import glslVisitor;

import sdflib;
import sdfNode;
import DynamicShader;
import previewShader;
using namespace SDF;

using sdfNode = sdfTreeGroup<binOpVariant<float>, unaryOpVariant<float>, domainOpVariant<float>, shapeVariant<float>>;
using sdflib = SDFLIB<float, sdfNode>;

using namespace ivec;
using namespace codegen;
struct previewShaderAttrs {
	GLint cPos, vPos;
	GLLocation locations[2];
	previewShaderAttrs() {
		locations[0] = { &cPos, "cPos" }; locations[1] = { &vPos, "vPos" };
	}
};
struct previewShaderUnis {
	GLint o;
	GLint z;
	GLint mdl;
	GLLocation locations[3];
	previewShaderUnis()
	{
		locations[0] = { &o, "o" };
		locations[1] = { &z, "z" };
		locations[2] = { &mdl, "mdl" };
	}
};
template <typename F, typename GroupType>
	class previewShader : public StaticInterfaceShader<previewShaderAttrs, previewShaderUnis> {
	using fvec3 = imvec::vec<float, 3>;
	protected:
		
	public:
		previewShader(const typename GroupType::NodeVariant& sdfObj) : StaticInterfaceShader<previewShaderAttrs, previewShaderUnis>(codegen::getBasicVsrc(), codegen::buildDirectRenderShader<F, GroupType>(sdfObj)) {
			this->buildAndLink();
		}
		
};
float frand()
{
	unsigned int x = rand() % RAND_MAX;
	return ((float)x) / (float)RAND_MAX;
}
float rnd2() {
	return 2.0 * (frand() - 0.5f);
}

/**
sdfNode::NodeVariant&& cheesePlease(float s, unsigned int holes) {
	// make a scene by subtracting spheres from a cube
	using fvec3 = imvec::vec<float, 3>;
	sdfNode::Shape B = sdflib::Box(fvec3(s, s, s));
	auto obj = sdflib::Subtract(B, sdflib::Sphere(1.0f));
	for (unsigned int i = 0; i < holes; i++) {
		float r = frand() * (s / 100.0f);
		fvec3 offset = fvec3(rnd2(), rnd2(), rnd2()) * s;
		obj = sdflib::Subtract(std::move(obj), sdflib::Move(offset, sdflib::Sphere(r)));
	}
	return std::move(obj);
}
*/

void UpdateView(previewShader<float, sdfNode>* shader, mat<float, 4>& mdl, imvec::vec<float,3> & p, int screenWidth, int screenHeight) {
	OGL::checkError("start update");
	float clm[16];
	mdl.toColumnMajorArray(clm);
	OGL::BindFramebuffer(GL_FRAMEBUFFER, 0); // unbind as fbo...
	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0, 0, 0, 1);
	glClear(GL_DEPTH_BUFFER_BIT);
	shader->useProgram();
	OGL::checkError("use prg");
	OGL::Uniform3f(shader->Unis.o, p.x(), p.y(), p.z());
	OGL::Uniform1f(shader->Unis.z, p.z() + 1.0);
	OGL::UniformMatrix4fv(shader->Unis.mdl, 1, false, clm);
	float a = (float)screenHeight / (float)screenWidth;
	float w2 = 1.0;
	float h2 = a;
	float vPos[8] = { -w2, -h2, w2, -h2, w2, h2, -w2, h2 };
	uint8_t unitSquare[8] = { 0, 0, 255, 0, 255, 255, 0, 255 };
	OGL::EnableVertexAttribArray(shader->vAttrs.cPos);
	OGL::VertexAttribPointer(shader->vAttrs.cPos, 2, GL_UNSIGNED_BYTE, true, 0,
		unitSquare);

	OGL::EnableVertexAttribArray(shader->vAttrs.vPos);
	OGL::VertexAttribPointer(shader->vAttrs.vPos, 2, GL_FLOAT, false, 0, vPos);
	OGL::checkError("pre draw");
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	OGL::checkError("post draw");

}

#define WINDOWMODE WS_VISIBLE | WS_OVERLAPPEDWINDOW

#define MAX_LOADSTRING 100
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


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
	static bool showGUI = true;
	// mouse garbage: delete me please!
	static ivec2 lastMousePosScreenPx(0,0);
	static bool lDown = false;
	static bool rDown = false;
	static float camDistance = -12;
	static fvec3 camPoint(0, 0, camDistance);
	static float frametime = 0.0;
	static mat<float, 4> mdl;
	static previewShader<float, sdfNode>* shader = nullptr;
	static std::string clipboard;
	static sdfNode::NodeVariant objectThing = sdflib::Box(fvec3(50, 50, 50));// sdflib::Union(sdflib::Round(0.1, sdflib::Box(fvec3(0.5, 0.5, 0.5))), sdflib::Move(fvec3(0.5, 0, 0), sdflib::Sphere(0.6)));
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
		switch ((UINT)wParam)
		{
		case 'G':
			showGUI = !showGUI;
			break;
		case 'H':
		{
			glslHeaderVisitor<float, sdfNode> v;
			//std::cout<<glslStructName(box<float>(ivec::vec<float, 3>(1, 2, 3)));
			std::cout << glslLiteral(move<float>{ivec::vec<float, 3>(1, 2, 3)}) << std::endl;
			std::cout << glslLiteral(hexPrism<float>{3, 3}) << std::endl;
			std::visit([](const auto& arg) {std::cout << std::visit([](const auto& arg) {return glslStructName<float>(arg); }, arg.getPayload()) << std::endl; }, objectThing);
			v.visit(objectThing);
			v.blurt();
			glslDirectCallVisitor<float, sdfNode> dV("p");
			dV.visit(objectThing);
			std::cout << dV.getExpr() << std::endl;
		}
		break;
		case 'B':
		{
			unsigned int holes = 30;
			float s = 50.0f;
			for (unsigned int i = 0; i < holes; i++) {
				float r = frand() * (s / 3.0f);
				fvec3 offset = fvec3(rnd2(), rnd2(), rnd2()) * s;
				objectThing = sdflib::Subtract(0.5, std::move(objectThing), sdflib::Move(offset, sdflib::Sphere(r)));
			}
		}
		break;
		case 'R':
			if (shader != nullptr) {
				delete shader;
			}
			shader = new previewShader<float, sdfNode>(objectThing);
			break;
		}
	}
	break;
	case WM_CREATE:
	{

		hdc = GetWindowDC(hWnd);
		// setup pixel format request
		PIXELFORMATDESCRIPTOR pfd = getPreferredPixelFormatDescriptor();
		int pixform = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, pixform, &pfd);
		/**/
		int attribs[] = { WGL_CONTEXT_MAJOR_VERSION_ARB, 3, WGL_CONTEXT_MINOR_VERSION_ARB, 3, WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, 0, 0 };
		HGLRC hRC = getContext(hdc, attribs);
		if (hRC) {
			if (!bindRequiredExtensions(hdc)) {
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
		const GLubyte* str = glGetString(GL_VERSION);
		std::cout << "OGL reports version: " << str << std::endl;

		// IM GUI //
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplOpenGL3_Init("#version 130");
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		/**/

		// some random OGL state:
		glClearColor(0, 0, 0, 0);


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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// IMGUI //
		if (shader != nullptr) {
			UpdateView(shader, mdl, camPoint, screenWidth, screenHeight);
		}
		if (showGUI) {
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			// draw the gui
			auto result = guiVisit<float,sdfNode>(objectThing);
			auto nPtr = std::get_if<sdfNode::NodeVariant>(&result);
			if (nPtr != nullptr) {
				objectThing = *nPtr;
			}
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

