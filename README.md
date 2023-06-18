# Try2Engine
Cross-platform open-source 2D/3D game engine in the works. </br>
Licensed under GPLv3 (and will continue to be), hence using it as a template or basis for other projects is permitted. </br>
All libraries utilized in this project must be royalty free.
 
module | library  | description
---------| -------- | ------ 
Window | [SDL3](https://github.com/libsdl-org/SDL) | Initialize and create a window. Hook input, renderer, audio and others
2D Renderer | [SDL3*](https://github.com/libsdl-org/SDL)| 2D images, textures, sprites, and in the future - tilemaps
3D Render | ?? (TBD) | Render 3D meshes, models, skeletons and or more
Audio | ?? (TBD) | Play and mix audio queues on demand
2D Asset loading | [STB_image](https://github.com/nothings/stb) [SDL_Image](https://github.com/libsdl-org/SDL_image) | Image loading 
Input | [SDL3](https://github.com/libsdl-org/SDL) | Polling data sent from input devices; Connect/Disconnect, create and destroy controllers
Logger | [spdlog](https://github.com/gabime/spdlog) | Logging messages, errors and more  
GUI | [ImGui](https://github.com/ocornut/imgui) | GUI for in-engine windows and widgets (object properties, settings modifications and others)
Tests | [gtest](https://github.com/google/googletest) | Testing of modules and logic
Build Tool | [CMake](https://cmake.org/) | Building project on different platforms (tested on Linux Mint and Windows)

### **Build and run**
- `Windows (tested on Windows 11):` </br>
    Requires a pre-installed CMake(3.15 and above) and a C++ compiler (MSVC) with C++17 support. </br>
    1. Choose a configuration - Debug or Release
    2. Run its corresponding batch file - GenerateAndBuild<Debug/Release>X64.bat, located in the root folder of the project
    3. a: Execute Run.bat </br>
       b: Navigate to ./build/<Debug/Release>, and run try1.exe

- `Linux (testedo on Linux Mint):` </br>
    Requires a pre-installed CMake, C++, X11 (for SDL) and GLFW (for Box2D) toolkit. For ease of use, these are the commands used to retrieve those kits during the development of the project:
    - ``` sudo apt-get install cmake ```
    - ``` sudo apt-get install build-essential ```
    - ``` sudo apt-get install libx11-dev ```
    - ``` sudo apt-get install xorg-dev libglul-mesa-dev ``` 
    1. Choose a configuration - Debug or Release
    2. Run its corresponding shell script - GenerateAndBuild<Debug/Release>X64.sh, located in the root folder of the project
    3. a: Execute Run.sh </br>
       b: Navigate to ./build/tr1, and run try1

### **Philosophy and how to contribute?**
Project with modular architecture. </br>
Every module in the project should be implemented with the intend that its libraries could change in the future. </br>
This project adheres to the principle that every module should be initially implemented as an **adapter**, **facade**, **template** or a similar structural and creational patterns. This approach enables the internals of each module to evolve independently, while the code that utilizes each module remains unchanged. </br>
_*Creational*_ patterns are up to personal preference. </br>
All libraries should be either **vendored** (and added as submodules) or fetched in a `CMake` configuration file
