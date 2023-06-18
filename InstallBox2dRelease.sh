cd ./engine/libraries/box2d &&
rm -rf "./build" &&  
rm -rf "./install" &&  
cmake -S . -B ./build &&
cmake --build ./build --config Release &&
cmake --install ./build --prefix ./install --config Release