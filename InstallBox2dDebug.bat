cd ./engine/libraries/box2d
rd /s /q "./install"
rd /s /q "./build"
cmake -S . -B ./build
cmake --build ./build --config Debug
cmake --install ./build --prefix ./install --config Debug