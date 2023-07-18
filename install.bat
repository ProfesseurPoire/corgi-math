@setlocal enableextensions
@cd /d "%~dp0"

rmdir /s /q "C:\Program Files\corgi-math"

for %%i in (x64) do (

    setlocal

    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" %%i
    
    for %%j in (Debug Release) do (
        setlocal
        mkdir build\build%%i\%%j
        cd build\build%%i\%%j

  	  cmake -DCMAKE_BUILD_TYPE=%%j -DCMAKE_INSTALL_PREFIX="C:\\Program Files\\corgi-math" -DBUILD_TESTS=OFF -DBUILD_EXAMPLES=OFF -G "Visual Studio 17 2022"  ..\..\..

        
        msbuild INSTALL.vcxproj /property:Configuration=%%j    
        endlocal
    )
    endlocal
)
