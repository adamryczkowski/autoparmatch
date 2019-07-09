# autoparmatch
Automatic parameter matching by name in C++ based on boost::Hana

C++ is statically typed, so when you call a function that accepts a lot of arguments and you mess with the order, or skipped one or two arguments, the compiler hopefully would catch it. 

Unless all/most of the arguments have the same type. 

This is where this library might help you. It allows you to use a compile-time dictionary of pairs (parameter name, argument) to feed a function with all the necessary arguments. The called function will simply pick up whatever arguments it happen to need from the dictionary, all in compile time. 

The function might consume those arguments in the form of the (similar) compile-time dictionary (parameter name, argument), or by position. The choice is given to the user by the macro `POSITIONAL`.

Internally, most of the magic happens using Boost::hana 1.69.0 or newer.

There are some caveats:

* First of all, in general, metaprogramming libraries are *slow* to compile, produce *unintelligible* compile error messages and require *extra skills* to manage. So even it seems tempting to use, be carefull not to overengineer your code. 
* CUDA `nvcc` is *not* compatible with Boost::hana, despite it claims to support c++14. It means that only the called function can be implemented in CUDA, and it *must* use positional argument passing (i.e. the function signature is plain, not using Boost::hana stuff).
* Arguments are passed by value (but that is easy to remedy by using (smart) pointers)


# Building

The code can be build using CMake. There are two modes: either by using my general-purpose CMake embedded language/library "The Beetroot", or with plain CMake. If you downloaded the beetroot git submodule, it will compile using it. Otherwise, if the library "beetroot" is absent, it will default to the plain CMake, but it will only build one version of the test executable one that uses both `POSITIONAL` and `NAMED` call. To get other versions you will need to change the CMake cache variables using e.g. `ccmake` or `cmake-gui`.
