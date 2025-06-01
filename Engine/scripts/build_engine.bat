@echo off

REM Batch script for building the Engine

REM Steps:
REM  1.- Build dependencies
REM  2.- Move DLLs
REM  3.- Build engine solution

REM Store PATHS
cd ..
set SolutionDir=%cd%
set Exes=%SolutionDir%\exes

echo %Exes%

set SDL2_DLLS_PATH=%SolutionDir%\dependencies\SDL2\lib\SDL2.dll
set SDL2TTF_DLLS_PATH=%SolutionDir%\dependencies\SDL2_ttf\lib\SDL2_ttf.dll
set SDL2IMAGE_DLLS_PATH=%SolutionDir%\dependencies\SDL2_image\lib\SDL2_image.dll
set SDL2IMIXER_DLLS_PATH=%SolutionDir%\dependencies\SDL2_mixer\lib\SDL2_mixer.dll



REM First of all, go to root directory (SolutionDir)
cd %SolutionDir%

REM Step 1 Build dependencies

cd dependencies\Box2D
call build.bat

cd build
msbuild box2d.sln /p:Configuration=Debug /p:Platform=x64 
msbuild box2d.sln /p:Configuration=Release /p:Platform=x64 

REM Step 2 Move DLLs

cd %SolutionDir%
mkdir exes
copy %SDL2_DLLS_PATH% %Exes%
copy %SDL2TTF_DLLS_PATH% %Exes%
copy %SDL2IMAGE_DLLS_PATH% %Exes%
copy %SDL2IMIXER_DLLS_PATH% %Exes%


REM Step 3 Build engine solution

cd %SolutionDir%
msbuild Engine.sln /p:Configuration=Debug /p:Platform=x64 
msbuild Engine.sln /p:Configuration=Release /p:Platform=x64 


echo Build Successfull!