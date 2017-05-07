# ShiVa20EditorBinaryModule
DLL, DYLIB and SO modules for ShiVa 2.0 Editor, C++/Lua integration

# Usage of ShiVa 2.0 Editor Binary Modules
1. Copy module binary to:

- Windows: ShiVa 2.0 Editor installation directory root
- Linux: ShiVa 2.0 Editor installation directory root
- Mac: anywhere, but requires absolute path in Lua package.loadlib() call

2. Call library from Lua using code provided in luaForShiVa.txt

# Building Modules
Demo Projects are included for:

- Windows: Visual Studio 2015 (vs140) in C++
- Linux: Code::Blocks (gcc) in C++
- Mac: Xcode 7 (OSX 10.12) in Obj-C++ (.mm)

# Tutorial
A Tutorial for Windows is available here: http://www.shiva-engine.com/shiva-lua-unlocked-pt2-editor-dll-modules/