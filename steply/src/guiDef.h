#pragma once

#define decl_uiName(type, name) \
template <typename F> \
const char* uiName(const type<F>& node){return name;} \

// typedefs for callables...
template <typename F>
using editFn = F (*)(const char* lbl, F value, bool* changed);

