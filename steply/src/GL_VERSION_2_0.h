#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include "glext.h"
#ifndef OPENGL_REQUIRED_GETPROCADDRESS
#define OPENGL_REQUIRED_GETPROCADDRESS(type, func) \
	func = (type)wglGetProcAddress(#func);
#endif
/// GL_VERSION_2_0 ///
namespace _gl {
bool bindGL_VERSION_2_0(const char* extensionString);
namespace VERSION_2_0 {
void BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
void DrawBuffers(GLsizei n, const GLenum *bufs);
void StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
void StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
void StencilMaskSeparate(GLenum face, GLuint mask);
void AttachShader(GLuint program, GLuint shader);
void BindAttribLocation(GLuint program, GLuint index, const GLchar *name);
void CompileShader(GLuint shader);
GLuint CreateProgram();
GLuint CreateShader(GLenum type);
void DeleteProgram(GLuint program);
void DeleteShader(GLuint shader);
void DetachShader(GLuint program, GLuint shader);
void DisableVertexAttribArray(GLuint index);
void EnableVertexAttribArray(GLuint index);
void GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
void GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
void GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
GLint GetAttribLocation(GLuint program, const GLchar *name);
void GetProgramiv(GLuint program, GLenum pname, GLint *params);
void GetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
void GetShaderiv(GLuint shader, GLenum pname, GLint *params);
void GetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
void GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
GLint GetUniformLocation(GLuint program, const GLchar *name);
void GetUniformfv(GLuint program, GLint location, GLfloat *params);
void GetUniformiv(GLuint program, GLint location, GLint *params);
void GetVertexAttribdv(GLuint index, GLenum pname, GLdouble *params);
void GetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params);
void GetVertexAttribiv(GLuint index, GLenum pname, GLint *params);
void GetVertexAttribPointerv(GLuint index, GLenum pname, void **pointer);
GLboolean IsProgram(GLuint program);
GLboolean IsShader(GLuint shader);
void LinkProgram(GLuint program);
void ShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
void UseProgram(GLuint program);
void Uniform1f(GLint location, GLfloat v0);
void Uniform2f(GLint location, GLfloat v0, GLfloat v1);
void Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
void Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
void Uniform1i(GLint location, GLint v0);
void Uniform2i(GLint location, GLint v0, GLint v1);
void Uniform3i(GLint location, GLint v0, GLint v1, GLint v2);
void Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
void Uniform1fv(GLint location, GLsizei count, const GLfloat *value);
void Uniform2fv(GLint location, GLsizei count, const GLfloat *value);
void Uniform3fv(GLint location, GLsizei count, const GLfloat *value);
void Uniform4fv(GLint location, GLsizei count, const GLfloat *value);
void Uniform1iv(GLint location, GLsizei count, const GLint *value);
void Uniform2iv(GLint location, GLsizei count, const GLint *value);
void Uniform3iv(GLint location, GLsizei count, const GLint *value);
void Uniform4iv(GLint location, GLsizei count, const GLint *value);
void UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
void UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
void ValidateProgram(GLuint program);
void VertexAttrib1d(GLuint index, GLdouble x);
void VertexAttrib1dv(GLuint index, const GLdouble *v);
void VertexAttrib1f(GLuint index, GLfloat x);
void VertexAttrib1fv(GLuint index, const GLfloat *v);
void VertexAttrib1s(GLuint index, GLshort x);
void VertexAttrib1sv(GLuint index, const GLshort *v);
void VertexAttrib2d(GLuint index, GLdouble x, GLdouble y);
void VertexAttrib2dv(GLuint index, const GLdouble *v);
void VertexAttrib2f(GLuint index, GLfloat x, GLfloat y);
void VertexAttrib2fv(GLuint index, const GLfloat *v);
void VertexAttrib2s(GLuint index, GLshort x, GLshort y);
void VertexAttrib2sv(GLuint index, const GLshort *v);
void VertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z);
void VertexAttrib3dv(GLuint index, const GLdouble *v);
void VertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z);
void VertexAttrib3fv(GLuint index, const GLfloat *v);
void VertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z);
void VertexAttrib3sv(GLuint index, const GLshort *v);
void VertexAttrib4Nbv(GLuint index, const GLbyte *v);
void VertexAttrib4Niv(GLuint index, const GLint *v);
void VertexAttrib4Nsv(GLuint index, const GLshort *v);
void VertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
void VertexAttrib4Nubv(GLuint index, const GLubyte *v);
void VertexAttrib4Nuiv(GLuint index, const GLuint *v);
void VertexAttrib4Nusv(GLuint index, const GLushort *v);
void VertexAttrib4bv(GLuint index, const GLbyte *v);
void VertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
void VertexAttrib4dv(GLuint index, const GLdouble *v);
void VertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void VertexAttrib4fv(GLuint index, const GLfloat *v);
void VertexAttrib4iv(GLuint index, const GLint *v);
void VertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
void VertexAttrib4sv(GLuint index, const GLshort *v);
void VertexAttrib4ubv(GLuint index, const GLubyte *v);
void VertexAttrib4uiv(GLuint index, const GLuint *v);
void VertexAttrib4usv(GLuint index, const GLushort *v);
void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
} // end namespace VERSION_2_0
} // end namespace _gl
