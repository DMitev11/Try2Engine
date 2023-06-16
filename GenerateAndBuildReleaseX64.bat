git submodule update --init --recursive
InstallSDLReleaseX64.bat
cmake -S . -B ./build -DWITH_SDL=TRUE -DWITH_STB=TRUE -DWITH_IMGUI=TRUE -DWITH_BOX2D=TRUE 
cmake --build ./build 