# smallWiener
<!-- Description to be added. -->

## Getting Involved
Contributing to smallWiener requires [Godot](https://godotengine.org), version `3.4.5`.

### Building
Certain parts of smallWiener are written in C++ as a measure to keep large logic blocks concise and fast.

Building those components requires:
- A decent C++ compiler, i.e [clang/LLVM](https://llvm.org), which is what we use
- [CMake](https://cmake.org) and a build system beneath it, we use [Ninja](https://ninja-build.org/)
- [godot-cpp](https://github.com/godotengine/godot-cpp) for the version of Godot we're using, it's available as a submodule

Then just run CMake:
```sh
cmake -B build -G Ninja
cmake --build build -j8
```

And it'll build a release version DLL.  
The project is already set up to load the DLL correctly; just open the project in Godot.  
The code can be changed, recompiled and used immediately merely by restarting simulation in Godot.
