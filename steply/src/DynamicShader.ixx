module;
#include <string>
#include <iostream>
#include "OGL.h"
export module DynamicShader;

export GLint;

export struct Handles {
	GLhandleARB vertexShader;
	GLhandleARB fragmentShader;
	GLhandleARB program;
	Handles() {
		program = 0;
		vertexShader = 0;
		fragmentShader = 0;
	}
};
export struct GLLocation {
	GLint* loc;
	const char* name;
};

export template <typename Attrs, typename Uniforms>
class StaticInterfaceShader {
protected:
	Handles handles;
	std::string vSrc, fSrc;
public:
	Attrs vAttrs;
	Uniforms Unis;
	StaticInterfaceShader(std::string vsrc, std::string fsrc) : vSrc(vsrc), fSrc(fsrc) {

	}
	virtual ~StaticInterfaceShader() {
		std::cout << "delete program: " << handles.program << std::endl;
		// we deleted the shader handles after building - 
		// now delete this last one!

		OGL::DeleteProgram(handles.program);
		OGL::checkError("del prog\n");
	}
protected:
	bool buildShader(const std::string& vSrc, const std::string& fSrc) {
		handles.vertexShader = OGL::CreateShader(GL_VERTEX_SHADER_ARB);
		handles.fragmentShader = OGL::CreateShader(GL_FRAGMENT_SHADER_ARB);
		handles.program = OGL::CreateProgram();
		unsigned int vLen = vSrc.length();
		unsigned int fLen = fSrc.length();
		GLint vLens[] = { vLen };
		GLint fLens[] = { fLen };
		const char* vlines = vSrc.c_str();
		const char* flines = fSrc.c_str();
		OGL::ShaderSource(handles.vertexShader, 1, &vlines, vLens);
		OGL::ShaderSource(handles.fragmentShader, 1, &flines, fLens);
		// neat, compile and link!
		OGL::CompileShader(handles.vertexShader);
		OGL::CompileShader(handles.fragmentShader);
		unsigned int bufSize = 2048;
		GLchar buffer[2048];
		GLint infoLen = 0;
		bool stopAfterCompile = false;
		GLint status = 0;
		OGL::GetShaderiv(handles.vertexShader, GL_COMPILE_STATUS, &status);
		if (!status) {
			OGL::GetShaderInfoLog(handles.vertexShader, bufSize, &infoLen, buffer);
			std::cout << "Error compiling vertex shader: " << buffer << std::endl;
			stopAfterCompile = true;
		}
		OGL::GetShaderiv(handles.fragmentShader, GL_COMPILE_STATUS, &status);
		if (!status) {
			OGL::GetShaderInfoLog(handles.fragmentShader, bufSize, &infoLen, buffer);
			std::cout << "Error compiling fragment shader: " << buffer << std::endl;
			stopAfterCompile = true;
		}
		if (stopAfterCompile) {
			return false;
		}
		// attach them to the program....
		OGL::AttachShader(handles.program, handles.vertexShader);
		OGL::AttachShader(handles.program, handles.fragmentShader);
		GLint linkStatus = 0;
		GLint validateStatus = 0;
		OGL::LinkProgram(handles.program);
		OGL::GetProgramiv(handles.program, GL_LINK_STATUS, &linkStatus);
		if (!linkStatus) {
			OGL::GetProgramInfoLog(handles.program, bufSize, &infoLen, buffer);
			std::cout << "Error linking shader: " << buffer << std::endl;
			return false;
		}
		OGL::ValidateProgram(handles.program);
		OGL::GetProgramiv(handles.program, GL_VALIDATE_STATUS, &validateStatus);
		if (!validateStatus) {
			OGL::GetProgramInfoLog(handles.program, bufSize, &infoLen, buffer);
			std::cout << "Error Validating shader: " << buffer << std::endl;
			return false;
		}
		// after a successful link - we can delete the shader objects...
		OGL::DeleteShader(handles.vertexShader);
		OGL::DeleteShader(handles.fragmentShader);
		// should we detatch them? TODO
		return true;
	}
	void linkLocations() {
		for (GLLocation attr : vAttrs.locations) {
			*(attr.loc) = OGL::GetAttribLocation(handles.program, attr.name);
		}
		for (GLLocation uni : Unis.locations) {
			*(uni.loc) = OGL::GetUniformLocation(handles.program, uni.name);
		}
	}
public:
	bool buildAndLink() {
		if (handles.program != 0) {
			std::cerr << "HEY! it looks like you're trying to re-build a shader, possibly with a differnt GLSL version! this is not supported" << std::endl;
			return false;
		}
		if (buildShader(vSrc, fSrc)) {
			linkLocations();
			return true;
		}
		return false;
	}
	Attrs attrLocations() {
		return vAttrs;
	}
	Uniforms uniformLocations() {
		return Unis;
	}
	void useProgram() {
		if (handles.program == 0) {
			// hmmm before there were glsl version variants - we could auto-build.
			std::cerr << "HEY ERROR: cant use shader before building" << std::endl;
			return;
		}
		OGL::UseProgram(handles.program);
	}
};