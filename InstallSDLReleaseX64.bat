cd engine/libraries/SDL
rd /s /q "./install"
rd /s /q "./build"
cmake -DCMAKE_CXX_FLAGS=-m64 -DCMAKE_SHARED_LINKER_FLAGS=-m64 -S . -B ./build
cmake --build ./build --config Release
cmake --install ./build --prefix ./install --config Release
cd ../SDL_Image
rd /s /q "./install"
rd /s /q "./build"
cmake -DCMAKE_CXX_FLAGS=-m64 -DCMAKE_SHARED_LINKER_FLAGS=-m64 -DSDL3_DIR=../SDL/install/cmake/ -S . -B ./build
cmake --build ./build --config Release 
cmake --install ./build --prefix ./install --config Release 