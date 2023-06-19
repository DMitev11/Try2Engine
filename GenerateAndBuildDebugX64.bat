git submodule update --init --recursive
call InstallSDLDebugX64.bat  
rem Back to root folder 
cd %~dp0\% 
call InstallBox2dDebug.bat 
rem Back to root folder
cd %~dp0\% 
cmake -S . -B ./build -DWITH_SDL=TRUE -DWITH_STB=TRUE -DWITH_IMGUI=TRUE -DWITH_BOX2D=TRUE  
cmake --build ./build 