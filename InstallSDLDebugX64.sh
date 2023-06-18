rm -rf "./engine/libraries/SDL/build" &&
cd engine/libraries/SDL &&
cmake -DCMAKE_CXX_FLAGS=-m64 -DCMAKE_SHARED_LINKER_FLAGS=-m64 -S . -B ./build &&
cmake --build ./build --config Debug &&
cmake --install ./build --prefix ./install --config Debug 