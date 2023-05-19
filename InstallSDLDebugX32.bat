cd engine/libraries/SDL
cmake -DCMAKE_CXX_FLAGS=-m32 -DCMAKE_SHARED_LINKER_FLAGS=-m32 -S . -B ./build
cmake --build ./build --config Debug
cmake --install ./build --prefix ./install --config Debug
cd ../SDL_Image
cmake -DCMAKE_CXX_FLAGS=-m32 -DCMAKE_SHARED_LINKER_FLAGS=-m32 -DSDL3_DIR=../SDL/install/cmake/ -S . -B ./build
cmake --build ./build --config Debug 
cmake --install ./build --prefix ./install --config Debug