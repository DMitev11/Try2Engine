#Linux
git submodule update --init --recursive &&
chmod +x InstallSDLDebugX64.sh && 
sh InstallSDLDebugX64.sh && 
cd "$(dirname "0")" &&
chmod +x InstallBox2dDebug.sh && 
sh InstallBox2dDebug.sh &&    
cd "$(dirname "0")" &&
cmake -S . -B ./build -DWITH_SDL=TRUE -DWITH_STB=TRUE -DWITH_IMGUI=TRUE -DWITH_BOX2D=TRUE &&
cmake --build ./build
