cd ./engine/libraries/box2d
cmake -S . -B ./build
cmake --build ./build --config Debug
cmake --install ./build --prefix ./install --config Debug