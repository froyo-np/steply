#pragma once
#define decl_uiName(type, name) \
template <typename F> \
constexpr const char* uiName(const type<F>& node){return name;} \

#define decl_glslFunc(fnName, sName, fnBody) "float " fnName "(" sName " self, vec3 p){\n " fnBody "\n}\n"

#define decl_glslInterface(cppName, sName, sDef, fnName, fnDef) \
export template <typename F> \
const char* glslStructName(const cppName<F>& p){return sName;} \
export template <typename F> \
const char* glslStructDef(const cppName<F>& p){return sDef;} \
export template <typename F> \
const char* glslFnName(const cppName<F>& p){return fnName;} \
export template <typename F> \
const char* glslFnDef(const cppName<F>& p){return fnDef;} \


