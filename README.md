# steply
SDF math library - for rendering stuff with SDF functions.
future plan: make it run in WASM
## purpose
you can see that c++20 modules are used, hence the .ixx files. Also planned for use is some (new to me) use of patterns like type-erasure, at least to some degree - I might just stop at (static) polymorphism by way of overloading.
## build?
for now, use Visual studio 2022, c++20. This repo should be buildable by way of Clang -std=c++20 -fmodules, but I haven't made that work yet, since you have to type a bunch of stuff, wheras visual studio just makes it work
