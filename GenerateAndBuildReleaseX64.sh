#Linux
git submodule update --init --recursive &&
chmod +x InstallSDLReleaseX64.sh && 
sh InstallSDLReleaseX64.sh && 
cd sh &&
chmod +x InstallBox2dRelease.sh && 
sh InstallBox2dRelease.sh &&    
cd sh &&
cmake -S . -B ./build -DWITH_SDL=TRUE -DWITH_STB=TRUE -DWITH_IMGUI=TRUE -DWITH_BOX2D=TRUE &&
cmake --build ./build 