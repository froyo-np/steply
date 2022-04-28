#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include "glext.h"
#ifndef OPENGL_REQUIRED_GETPROCADDRESS
#define OPENGL_REQUIRED_GETPROCADDRESS(type, func) \
	func = (type)wglGetProcAddress(#func);
#endif
/// GL_VERSION_3_0 ///
namespace _gl {
bool bindGL_VERSION_3_0(const char* extensionString);
namespace VERSION_3_0 {
void ColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
void GetBooleani_v(GLenum target, GLuint index, GLboolean *data);
void GetIntegeri_v(GLenum target, GLuint index, GLint *data);
void Enablei(GLenum target, GLuint index);
void Disablei(GLenum target, GLuint index);
GLboolean IsEnabledi(GLenum target, GLuint index);
void BeginTransformFeedback(GLenum primitiveMode);
void EndTransformFeedback();
void BindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
void BindBufferBase(GLenum target, GLuint index, GLuint buffer);
void TransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode);
void GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
void ClampColor(GLenum target, GLenum clamp);
void BeginConditionalRender(GLuint id, GLenum mode);
void EndConditionalRender();
void VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
void GetVertexAttribIiv(GLuint index, GLenum pname, GLint *params);
void GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint *params);
void VertexAttribI1i(GLuint index, GLint x);
void VertexAttribI2i(GLuint index, GLint x, GLint y);
void VertexAttribI3i(GLuint index, GLint x, GLint y, GLint z);
void VertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w);
void VertexAttribI1ui(GLuint index, GLuint x);
void VertexAttribI2ui(GLuint index, GLuint x, GLuint y);
void VertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z);
void VertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
void VertexAttribI1iv(GLuint index, const GLint *v);
void VertexAttribI2iv(GLuint index, const GLint *v);
void VertexAttribI3iv(GLuint index, const GLint *v);
void VertexAttribI4iv(GLuint index, const GLint *v);
void VertexAttribI1uiv(GLuint index, const GLuint *v);
void VertexAttribI2uiv(GLuint index, const GLuint *v);
void VertexAttribI3uiv(GLuint index, const GLuint *v);
void VertexAttribI4uiv(GLuint index, const GLuint *v);
void VertexAttribI4bv(GLuint index, const GLbyte *v);
void VertexAttribI4sv(GLuint index, const GLshort *v);
void VertexAttribI4ubv(GLuint index, const GLubyte *v);
void VertexAttribI4usv(GLuint index, const GLushort *v);
void GetUniformuiv(GLuint program, GLint location, GLuint *params);
void BindFragDataLocation(GLuint program, GLuint color, const GLchar *name);
GLint GetFragDataLocation(GLuint program, const GLchar *name);
void Uniform1ui(GLint location, GLuint v0);
void Uniform2ui(GLint location, GLuint v0, GLuint v1);
void Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2);
void Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
void Uniform1uiv(GLint location, GLsizei count, const GLuint *value);
void Uniform2uiv(GLint location, GLsizei count, const GLuint *value);
void Uniform3uiv(GLint location, GLsizei count, const GLuint *value);
void Uniform4uiv(GLint location, GLsizei count, const GLuint *value);
void TexParameterIiv(GLenum target, GLenum pname, const GLint *params);
void TexParameterIuiv(GLenum target, GLenum pname, const GLuint *params);
void GetTexParameterIiv(GLenum target, GLenum pname, GLint *params);
void GetTexParameterIuiv(GLenum target, GLenum pname, GLuint *params);
void ClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint *value);
void ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint *value);
void ClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value);
void ClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
const GLubyte * GetStringi(GLenum name, GLuint index);
GLboolean IsRenderbuffer(GLuint renderbuffer);
void BindRenderbuffer(GLenum target, GLuint renderbuffer);
void DeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers);
void GenRenderbuffers(GLsizei n, GLuint *renderbuffers);
void RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
void GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params);
GLboolean IsFramebuffer(GLuint framebuffer);
void BindFramebuffer(GLenum target, GLuint framebuffer);
void DeleteFramebuffers(GLsizei n, const GLuint *framebuffers);
void GenFramebuffers(GLsizei n, GLuint *framebuffers);
GLenum CheckFramebufferStatus(GLenum target);
void FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
void FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
void FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
void FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
void GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params);
void GenerateMipmap(GLenum target);
void BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
void RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
void FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
void * MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
void FlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length);
void BindVertexArray(GLuint array);
void DeleteVertexArrays(GLsizei n, const GLuint *arrays);
void GenVertexArrays(GLsizei n, GLuint *arrays);
GLboolean IsVertexArray(GLuint array);
} // end namespace VERSION_3_0
} // end namespace _gl
