cd ./engine/libraries/box2d &&
cmake -S . -B ./build &&
cmake --build ./build --config Release &&
cmake --install ./build --prefix ./install --config Release