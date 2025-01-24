function BuildForWindows($targetPlatform, $vcpkgPath, $runMsbuild, $hostPlatform) {  
    # Set default host platform if not provided
    if (-not $hostPlatform) {
        $hostPlatform = "x64"
    }

    # Set build directory
    $buildDirectory = "build_win_${targetPlatform}"
    mkdir $buildDirectory -Force -ErrorAction Stop | Out-Null
    cd $buildDirectory
    Write-Host "Building in directory: $(pwd)"

    # Determine platform-specific settings
    if ($targetPlatform -eq "x64") {
        $targetProcessor = "AMD64"
        $msbuildPlatform = "x64"
        $msmfFlag = "ON"
        $caroteneFlag = "ON"
    }
    elseif ($targetPlatform -eq "arm64") {
        $targetProcessor = "ARM64"
        $msbuildPlatform = "ARM64"
        $msmfFlag = "ON"
        $caroteneFlag = "OFF"
    }
    else {
        $targetProcessor = "x86"
        $msbuildPlatform = "Win32"
        $msmfFlag = "OFF" # MSMF not supported on x86
        $caroteneFlag = "ON"
    }

    # Determine host processor
    if ($hostPlatform -eq "x64") {
        $hostProcessor = "AMD64"
    } elseif ($hostPlatform -eq "arm64") {
        $hostProcessor = "ARM64"
    } else {
        $hostProcessor = "x86"
    }

    # Handle cross-compiling
    $crossCompileOptions = ""
    if ($hostPlatform -ne $targetPlatform) {
        $crossCompileOptions = "-D CMAKE_CROSSCOMPILING=1"
    }

    # Run CMake configuration
    cmake -G "Visual Studio 17 2022" `
        -A $msbuildPlatform `
        $crossCompileOptions `
        -D CMAKE_SYSTEM_HOST_PROCESSOR=$hostProcessor `
        -D CMAKE_SYSTEM_PROCESSOR=$targetProcessor `
        -D CMAKE_SYSTEM_NAME=Windows `
        -D CMAKE_SYSTEM_VERSION=10.0 `
        -D CMAKE_BUILD_TYPE=Release `
        -D CMAKE_INSTALL_PREFIX=install `
        -D INSTALL_C_EXAMPLES=OFF `
        -D INSTALL_PYTHON_EXAMPLES=OFF `
        -D BUILD_DOCS=OFF `
        -D BUILD_WITH_DEBUG_INFO=OFF `
        -D BUILD_EXAMPLES=OFF `
        -D BUILD_TESTS=OFF `
        -D BUILD_PERF_TESTS=OFF `
        -D BUILD_JAVA=OFF `
        -D BUILD_opencv_world=OFF `
        -D WITH_MSMF=${msmfFlag} `
        -D WITH_QT=OFF `
        -D WITH_TESSERACT=ON `
        -D Tesseract_INCLUDE_DIR="${vcpkgPath}/installed/${targetPlatform}-windows-static/include" `
        -D Tesseract_LIBRARY="${vcpkgPath}/installed/${targetPlatform}-windows-static/lib/tesseract.lib" `
        -D Lept_LIBRARY="${vcpkgPath}/installed/${targetPlatform}-windows-static/lib/leptonica.lib" `
        -D ENABLE_CXX11=1 `
        -D OPENCV_ENABLE_NONFREE=ON `
        -D OPENCV_EXTRA_MODULES_PATH=../libs/opencv_contrib/modules `
        -D BUILD_SHARED_LIBS=OFF ../libs/opencv

    # Build the project with MSBuild if requested
    if ($runMsbuild) {
        Write-Host "Building with MSBuild for platform: $msbuildPlatform"
        msbuild INSTALL.vcxproj /t:build /p:configuration=Release /p:platform=$msbuildPlatform -maxcpucount
        Write-Host "Build completed. Listing build output:"
        ls
    }

    # Return to the parent directory
    cd ..
}

# Entry Point
if ((Resolve-Path -Path $MyInvocation.InvocationName).ProviderPath -eq $MyInvocation.MyCommand.Path) {
    # Target platform for the build
    $platform = "x64"

    # Ensure VCPKG dependencies are installed
    Write-Host "Installing Tesseract dependency with vcpkg for platform: $platform"
    Invoke-Expression "vcpkg install tesseract:${platform}-windows-static" -ErrorAction Stop

    # Start the build process
    BuildForWindows $platform $Env:VCPKG_ROOT $FALSE
}
