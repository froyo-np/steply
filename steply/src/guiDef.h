#pragma once

#define decl_uiName(type, name) \
template <typename F> \
constexpr const char* uiName(const type<F>& node){return name;} \

