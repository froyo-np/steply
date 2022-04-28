#include "GL_VERSION_3_0.h"
PFNGLCOLORMASKIPROC glColorMaski=nullptr;
PFNGLGETBOOLEANI_VPROC glGetBooleani_v=nullptr;
PFNGLGETINTEGERI_VPROC glGetIntegeri_v=nullptr;
PFNGLENABLEIPROC glEnablei=nullptr;
PFNGLDISABLEIPROC glDisablei=nullptr;
PFNGLISENABLEDIPROC glIsEnabledi=nullptr;
PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback=nullptr;
PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback=nullptr;
PFNGLBINDBUFFERRANGEPROC glBindBufferRange=nullptr;
PFNGLBINDBUFFERBASEPROC glBindBufferBase=nullptr;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings=nullptr;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying=nullptr;
PFNGLCLAMPCOLORPROC glClampColor=nullptr;
PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender=nullptr;
PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender=nullptr;
PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer=nullptr;
PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv=nullptr;
PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv=nullptr;
PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i=nullptr;
PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i=nullptr;
PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i=nullptr;
PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i=nullptr;
PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui=nullptr;
PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui=nullptr;
PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui=nullptr;
PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui=nullptr;
PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv=nullptr;
PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv=nullptr;
PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv=nullptr;
PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv=nullptr;
PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv=nullptr;
PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv=nullptr;
PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv=nullptr;
PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv=nullptr;
PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv=nullptr;
PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv=nullptr;
PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv=nullptr;
PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv=nullptr;
PFNGLGETUNIFORMUIVPROC glGetUniformuiv=nullptr;
PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation=nullptr;
PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation=nullptr;
PFNGLUNIFORM1UIPROC glUniform1ui=nullptr;
PFNGLUNIFORM2UIPROC glUniform2ui=nullptr;
PFNGLUNIFORM3UIPROC glUniform3ui=nullptr;
PFNGLUNIFORM4UIPROC glUniform4ui=nullptr;
PFNGLUNIFORM1UIVPROC glUniform1uiv=nullptr;
PFNGLUNIFORM2UIVPROC glUniform2uiv=nullptr;
PFNGLUNIFORM3UIVPROC glUniform3uiv=nullptr;
PFNGLUNIFORM4UIVPROC glUniform4uiv=nullptr;
PFNGLTEXPARAMETERIIVPROC glTexParameterIiv=nullptr;
PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv=nullptr;
PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv=nullptr;
PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv=nullptr;
PFNGLCLEARBUFFERIVPROC glClearBufferiv=nullptr;
PFNGLCLEARBUFFERUIVPROC glClearBufferuiv=nullptr;
PFNGLCLEARBUFFERFVPROC glClearBufferfv=nullptr;
PFNGLCLEARBUFFERFIPROC glClearBufferfi=nullptr;
PFNGLGETSTRINGIPROC glGetStringi=nullptr;
PFNGLISRENDERBUFFERPROC glIsRenderbuffer=nullptr;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer=nullptr;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers=nullptr;
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers=nullptr;
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage=nullptr;
PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv=nullptr;
PFNGLISFRAMEBUFFERPROC glIsFramebuffer=nullptr;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer=nullptr;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers=nullptr;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers=nullptr;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus=nullptr;
PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D=nullptr;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D=nullptr;
PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D=nullptr;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer=nullptr;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv=nullptr;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap=nullptr;
PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer=nullptr;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample=nullptr;
PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer=nullptr;
PFNGLMAPBUFFERRANGEPROC glMapBufferRange=nullptr;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange=nullptr;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray=nullptr;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays=nullptr;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays=nullptr;
PFNGLISVERTEXARRAYPROC glIsVertexArray=nullptr;
namespace _gl {
bool bindGL_VERSION_3_0(const char* extensionString){
bool success = true;
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLCOLORMASKIPROC, glColorMaski);
success &= (glColorMaski!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGETBOOLEANI_VPROC, glGetBooleani_v);
success &= (glGetBooleani_v!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGETINTEGERI_VPROC, glGetIntegeri_v);
success &= (glGetIntegeri_v!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLENABLEIPROC, glEnablei);
success &= (glEnablei!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLDISABLEIPROC, glDisablei);
success &= (glDisablei!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLISENABLEDIPROC, glIsEnabledi);
success &= (glIsEnabledi!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLBEGINTRANSFORMFEEDBACKPROC, glBeginTransformFeedback);
success &= (glBeginTransformFeedback!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLENDTRANSFORMFEEDBACKPROC, glEndTransformFeedback);
success &= (glEndTransformFeedback!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLBINDBUFFERRANGEPROC, glBindBufferRange);
success &= (glBindBufferRange!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLBINDBUFFERBASEPROC, glBindBufferBase);
success &= (glBindBufferBase!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLTRANSFORMFEEDBACKVARYINGSPROC, glTransformFeedbackVaryings);
success &= (glTransformFeedbackVaryings!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGETTRANSFORMFEEDBACKVARYINGPROC, glGetTransformFeedbackVarying);
success &= (glGetTransformFeedbackVarying!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLCLAMPCOLORPROC, glClampColor);
success &= (glClampColor!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLBEGINCONDITIONALRENDERPROC, glBeginConditionalRender);
success &= (glBeginConditionalRender!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLENDCONDITIONALRENDERPROC, glEndConditionalRender);
success &= (glEndConditionalRender!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBIPOINTERPROC, glVertexAttribIPointer);
success &= (glVertexAttribIPointer!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGETVERTEXATTRIBIIVPROC, glGetVertexAttribIiv);
success &= (glGetVertexAttribIiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGETVERTEXATTRIBIUIVPROC, glGetVertexAttribIuiv);
success &= (glGetVertexAttribIuiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI1IPROC, glVertexAttribI1i);
success &= (glVertexAttribI1i!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI2IPROC, glVertexAttribI2i);
success &= (glVertexAttribI2i!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI3IPROC, glVertexAttribI3i);
success &= (glVertexAttribI3i!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI4IPROC, glVertexAttribI4i);
success &= (glVertexAttribI4i!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI1UIPROC, glVertexAttribI1ui);
success &= (glVertexAttribI1ui!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI2UIPROC, glVertexAttribI2ui);
success &= (glVertexAttribI2ui!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI3UIPROC, glVertexAttribI3ui);
success &= (glVertexAttribI3ui!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI4UIPROC, glVertexAttribI4ui);
success &= (glVertexAttribI4ui!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI1IVPROC, glVertexAttribI1iv);
success &= (glVertexAttribI1iv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI2IVPROC, glVertexAttribI2iv);
success &= (glVertexAttribI2iv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI3IVPROC, glVertexAttribI3iv);
success &= (glVertexAttribI3iv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI4IVPROC, glVertexAttribI4iv);
success &= (glVertexAttribI4iv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI1UIVPROC, glVertexAttribI1uiv);
success &= (glVertexAttribI1uiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI2UIVPROC, glVertexAttribI2uiv);
success &= (glVertexAttribI2uiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI3UIVPROC, glVertexAttribI3uiv);
success &= (glVertexAttribI3uiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI4UIVPROC, glVertexAttribI4uiv);
success &= (glVertexAttribI4uiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI4BVPROC, glVertexAttribI4bv);
success &= (glVertexAttribI4bv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI4SVPROC, glVertexAttribI4sv);
success &= (glVertexAttribI4sv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI4UBVPROC, glVertexAttribI4ubv);
success &= (glVertexAttribI4ubv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLVERTEXATTRIBI4USVPROC, glVertexAttribI4usv);
success &= (glVertexAttribI4usv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGETUNIFORMUIVPROC, glGetUniformuiv);
success &= (glGetUniformuiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLBINDFRAGDATALOCATIONPROC, glBindFragDataLocation);
success &= (glBindFragDataLocation!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGETFRAGDATALOCATIONPROC, glGetFragDataLocation);
success &= (glGetFragDataLocation!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLUNIFORM1UIPROC, glUniform1ui);
success &= (glUniform1ui!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLUNIFORM2UIPROC, glUniform2ui);
success &= (glUniform2ui!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLUNIFORM3UIPROC, glUniform3ui);
success &= (glUniform3ui!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLUNIFORM4UIPROC, glUniform4ui);
success &= (glUniform4ui!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLUNIFORM1UIVPROC, glUniform1uiv);
success &= (glUniform1uiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLUNIFORM2UIVPROC, glUniform2uiv);
success &= (glUniform2uiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLUNIFORM3UIVPROC, glUniform3uiv);
success &= (glUniform3uiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLUNIFORM4UIVPROC, glUniform4uiv);
success &= (glUniform4uiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLTEXPARAMETERIIVPROC, glTexParameterIiv);
success &= (glTexParameterIiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLTEXPARAMETERIUIVPROC, glTexParameterIuiv);
success &= (glTexParameterIuiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGETTEXPARAMETERIIVPROC, glGetTexParameterIiv);
success &= (glGetTexParameterIiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGETTEXPARAMETERIUIVPROC, glGetTexParameterIuiv);
success &= (glGetTexParameterIuiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLCLEARBUFFERIVPROC, glClearBufferiv);
success &= (glClearBufferiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLCLEARBUFFERUIVPROC, glClearBufferuiv);
success &= (glClearBufferuiv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLCLEARBUFFERFVPROC, glClearBufferfv);
success &= (glClearBufferfv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLCLEARBUFFERFIPROC, glClearBufferfi);
success &= (glClearBufferfi!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGETSTRINGIPROC, glGetStringi);
success &= (glGetStringi!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLISRENDERBUFFERPROC, glIsRenderbuffer);
success &= (glIsRenderbuffer!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLBINDRENDERBUFFERPROC, glBindRenderbuffer);
success &= (glBindRenderbuffer!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLDELETERENDERBUFFERSPROC, glDeleteRenderbuffers);
success &= (glDeleteRenderbuffers!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGENRENDERBUFFERSPROC, glGenRenderbuffers);
success &= (glGenRenderbuffers!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLRENDERBUFFERSTORAGEPROC, glRenderbufferStorage);
success &= (glRenderbufferStorage!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGETRENDERBUFFERPARAMETERIVPROC, glGetRenderbufferParameteriv);
success &= (glGetRenderbufferParameteriv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLISFRAMEBUFFERPROC, glIsFramebuffer);
success &= (glIsFramebuffer!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer);
success &= (glBindFramebuffer!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLDELETEFRAMEBUFFERSPROC, glDeleteFramebuffers);
success &= (glDeleteFramebuffers!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers);
success &= (glGenFramebuffers!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLCHECKFRAMEBUFFERSTATUSPROC, glCheckFramebufferStatus);
success &= (glCheckFramebufferStatus!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLFRAMEBUFFERTEXTURE1DPROC, glFramebufferTexture1D);
success &= (glFramebufferTexture1D!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLFRAMEBUFFERTEXTURE2DPROC, glFramebufferTexture2D);
success &= (glFramebufferTexture2D!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLFRAMEBUFFERTEXTURE3DPROC, glFramebufferTexture3D);
success &= (glFramebufferTexture3D!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLFRAMEBUFFERRENDERBUFFERPROC, glFramebufferRenderbuffer);
success &= (glFramebufferRenderbuffer!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC, glGetFramebufferAttachmentParameteriv);
success &= (glGetFramebufferAttachmentParameteriv!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGENERATEMIPMAPPROC, glGenerateMipmap);
success &= (glGenerateMipmap!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLBLITFRAMEBUFFERPROC, glBlitFramebuffer);
success &= (glBlitFramebuffer!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC, glRenderbufferStorageMultisample);
success &= (glRenderbufferStorageMultisample!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLFRAMEBUFFERTEXTURELAYERPROC, glFramebufferTextureLayer);
success &= (glFramebufferTextureLayer!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLMAPBUFFERRANGEPROC, glMapBufferRange);
success &= (glMapBufferRange!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLFLUSHMAPPEDBUFFERRANGEPROC, glFlushMappedBufferRange);
success &= (glFlushMappedBufferRange!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray);
success &= (glBindVertexArray!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays);
success &= (glDeleteVertexArrays!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays);
success &= (glGenVertexArrays!=nullptr);
	OPENGL_REQUIRED_GETPROCADDRESS(PFNGLISVERTEXARRAYPROC, glIsVertexArray);
success &= (glIsVertexArray!=nullptr);
return success;
}
namespace VERSION_3_0 {
void ColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a){
	glColorMaski(index, r, g, b, a);
}
void GetBooleani_v(GLenum target, GLuint index, GLboolean *data){
	glGetBooleani_v(target, index, data);
}
void GetIntegeri_v(GLenum target, GLuint index, GLint *data){
	glGetIntegeri_v(target, index, data);
}
void Enablei(GLenum target, GLuint index){
	glEnablei(target, index);
}
void Disablei(GLenum target, GLuint index){
	glDisablei(target, index);
}
GLboolean IsEnabledi(GLenum target, GLuint index){
	return glIsEnabledi(target, index);
}
void BeginTransformFeedback(GLenum primitiveMode){
	glBeginTransformFeedback(primitiveMode);
}
void EndTransformFeedback(){
	glEndTransformFeedback();
}
void BindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size){
	glBindBufferRange(target, index, buffer, offset, size);
}
void BindBufferBase(GLenum target, GLuint index, GLuint buffer){
	glBindBufferBase(target, index, buffer);
}
void TransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode){
	glTransformFeedbackVaryings(program, count, varyings, bufferMode);
}
void GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name){
	glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
}
void ClampColor(GLenum target, GLenum clamp){
	glClampColor(target, clamp);
}
void BeginConditionalRender(GLuint id, GLenum mode){
	glBeginConditionalRender(id, mode);
}
void EndConditionalRender(){
	glEndConditionalRender();
}
void VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer){
	glVertexAttribIPointer(index, size, type, stride, pointer);
}
void GetVertexAttribIiv(GLuint index, GLenum pname, GLint *params){
	glGetVertexAttribIiv(index, pname, params);
}
void GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint *params){
	glGetVertexAttribIuiv(index, pname, params);
}
void VertexAttribI1i(GLuint index, GLint x){
	glVertexAttribI1i(index, x);
}
void VertexAttribI2i(GLuint index, GLint x, GLint y){
	glVertexAttribI2i(index, x, y);
}
void VertexAttribI3i(GLuint index, GLint x, GLint y, GLint z){
	glVertexAttribI3i(index, x, y, z);
}
void VertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w){
	glVertexAttribI4i(index, x, y, z, w);
}
void VertexAttribI1ui(GLuint index, GLuint x){
	glVertexAttribI1ui(index, x);
}
void VertexAttribI2ui(GLuint index, GLuint x, GLuint y){
	glVertexAttribI2ui(index, x, y);
}
void VertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z){
	glVertexAttribI3ui(index, x, y, z);
}
void VertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w){
	glVertexAttribI4ui(index, x, y, z, w);
}
void VertexAttribI1iv(GLuint index, const GLint *v){
	glVertexAttribI1iv(index, v);
}
void VertexAttribI2iv(GLuint index, const GLint *v){
	glVertexAttribI2iv(index, v);
}
void VertexAttribI3iv(GLuint index, const GLint *v){
	glVertexAttribI3iv(index, v);
}
void VertexAttribI4iv(GLuint index, const GLint *v){
	glVertexAttribI4iv(index, v);
}
void VertexAttribI1uiv(GLuint index, const GLuint *v){
	glVertexAttribI1uiv(index, v);
}
void VertexAttribI2uiv(GLuint index, const GLuint *v){
	glVertexAttribI2uiv(index, v);
}
void VertexAttribI3uiv(GLuint index, const GLuint *v){
	glVertexAttribI3uiv(index, v);
}
void VertexAttribI4uiv(GLuint index, const GLuint *v){
	glVertexAttribI4uiv(index, v);
}
void VertexAttribI4bv(GLuint index, const GLbyte *v){
	glVertexAttribI4bv(index, v);
}
void VertexAttribI4sv(GLuint index, const GLshort *v){
	glVertexAttribI4sv(index, v);
}
void VertexAttribI4ubv(GLuint index, const GLubyte *v){
	glVertexAttribI4ubv(index, v);
}
void VertexAttribI4usv(GLuint index, const GLushort *v){
	glVertexAttribI4usv(index, v);
}
void GetUniformuiv(GLuint program, GLint location, GLuint *params){
	glGetUniformuiv(program, location, params);
}
void BindFragDataLocation(GLuint program, GLuint color, const GLchar *name){
	glBindFragDataLocation(program, color, name);
}
GLint GetFragDataLocation(GLuint program, const GLchar *name){
	return glGetFragDataLocation(program, name);
}
void Uniform1ui(GLint location, GLuint v0){
	glUniform1ui(location, v0);
}
void Uniform2ui(GLint location, GLuint v0, GLuint v1){
	glUniform2ui(location, v0, v1);
}
void Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2){
	glUniform3ui(location, v0, v1, v2);
}
void Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3){
	glUniform4ui(location, v0, v1, v2, v3);
}
void Uniform1uiv(GLint location, GLsizei count, const GLuint *value){
	glUniform1uiv(location, count, value);
}
void Uniform2uiv(GLint location, GLsizei count, const GLuint *value){
	glUniform2uiv(location, count, value);
}
void Uniform3uiv(GLint location, GLsizei count, const GLuint *value){
	glUniform3uiv(location, count, value);
}
void Uniform4uiv(GLint location, GLsizei count, const GLuint *value){
	glUniform4uiv(location, count, value);
}
void TexParameterIiv(GLenum target, GLenum pname, const GLint *params){
	glTexParameterIiv(target, pname, params);
}
void TexParameterIuiv(GLenum target, GLenum pname, const GLuint *params){
	glTexParameterIuiv(target, pname, params);
}
void GetTexParameterIiv(GLenum target, GLenum pname, GLint *params){
	glGetTexParameterIiv(target, pname, params);
}
void GetTexParameterIuiv(GLenum target, GLenum pname, GLuint *params){
	glGetTexParameterIuiv(target, pname, params);
}
void ClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint *value){
	glClearBufferiv(buffer, drawbuffer, value);
}
void ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint *value){
	glClearBufferuiv(buffer, drawbuffer, value);
}
void ClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value){
	glClearBufferfv(buffer, drawbuffer, value);
}
void ClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil){
	glClearBufferfi(buffer, drawbuffer, depth, stencil);
}
const GLubyte * GetStringi(GLenum name, GLuint index){
	return glGetStringi(name, index);
}
GLboolean IsRenderbuffer(GLuint renderbuffer){
	return glIsRenderbuffer(renderbuffer);
}
void BindRenderbuffer(GLenum target, GLuint renderbuffer){
	glBindRenderbuffer(target, renderbuffer);
}
void DeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers){
	glDeleteRenderbuffers(n, renderbuffers);
}
void GenRenderbuffers(GLsizei n, GLuint *renderbuffers){
	glGenRenderbuffers(n, renderbuffers);
}
void RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height){
	glRenderbufferStorage(target, internalformat, width, height);
}
void GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params){
	glGetRenderbufferParameteriv(target, pname, params);
}
GLboolean IsFramebuffer(GLuint framebuffer){
	return glIsFramebuffer(framebuffer);
}
void BindFramebuffer(GLenum target, GLuint framebuffer){
	glBindFramebuffer(target, framebuffer);
}
void DeleteFramebuffers(GLsizei n, const GLuint *framebuffers){
	glDeleteFramebuffers(n, framebuffers);
}
void GenFramebuffers(GLsizei n, GLuint *framebuffers){
	glGenFramebuffers(n, framebuffers);
}
GLenum CheckFramebufferStatus(GLenum target){
	return glCheckFramebufferStatus(target);
}
void FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){
	glFramebufferTexture1D(target, attachment, textarget, texture, level);
}
void FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){
	glFramebufferTexture2D(target, attachment, textarget, texture, level);
}
void FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset){
	glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
}
void FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer){
	glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}
void GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params){
	glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}
void GenerateMipmap(GLenum target){
	glGenerateMipmap(target);
}
void BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter){
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}
void RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height){
	glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
}
void FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer){
	glFramebufferTextureLayer(target, attachment, texture, level, layer);
}
void * MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access){
	return glMapBufferRange(target, offset, length, access);
}
void FlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length){
	glFlushMappedBufferRange(target, offset, length);
}
void BindVertexArray(GLuint array){
	glBindVertexArray(array);
}
void DeleteVertexArrays(GLsizei n, const GLuint *arrays){
	glDeleteVertexArrays(n, arrays);
}
void GenVertexArrays(GLsizei n, GLuint *arrays){
	glGenVertexArrays(n, arrays);
}
GLboolean IsVertexArray(GLuint array){
	return glIsVertexArray(array);
}
} // end namespace VERSION_3_0
} // end namespace _gl
