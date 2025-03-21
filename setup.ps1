# Define installation directories
$RootDir = "$PSScriptRoot"
$HeadersDir = "$RootDir\headers"
$LibDir = "$RootDir\lib"
$TempDir = "$RootDir\temp"
$BuildDir = "$TempDir\build"

# Check if CMake is installed
if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    Write-Host "CMake is not installed. Please install CMake and try again."
    exit 1
}

# Create directories if they don't exist
New-Item -ItemType Directory -Path $HeadersDir -Force | Out-Null
New-Item -ItemType Directory -Path $LibDir -Force | Out-Null
New-Item -ItemType Directory -Path $TempDir -Force | Out-Null
New-Item -ItemType Directory -Path $BuildDir -Force | Out-Null

# Function to download and extract zip files
function Download-Extract($url, $destination) {
    $zipPath = "$TempDir\temp.zip"
    Invoke-WebRequest -Uri $url -OutFile $zipPath
    Expand-Archive -Path $zipPath -DestinationPath $destination -Force
    Remove-Item -Path $zipPath -Force
}

# Install GLM
Write-Host "Installing GLM..."
Download-Extract "https://github.com/g-truc/glm/archive/refs/tags/1.0.0.zip" $TempDir
Move-Item "$TempDir\glm-*\glm" "$HeadersDir\glm" -Force

# Install GLFW and build it as a static library
Write-Host "Installing GLFW..."
Download-Extract "https://github.com/glfw/glfw/archive/refs/tags/3.4.zip" $TempDir
$GLFWSourceDir = "$TempDir\glfw-3.4"
$GLFWBuildDir = "$BuildDir\glfw"
New-Item -ItemType Directory -Path $GLFWBuildDir -Force | Out-Null

# Run CMake to generate Visual Studio project files
Write-Host "Configuring GLFW build..."
Push-Location $GLFWBuildDir
cmake -G "Visual Studio 17 2022" -DBUILD_SHARED_LIBS=OFF -S $GLFWSourceDir -B $GLFWBuildDir

# Build GLFW using MSBuild
Write-Host "Building GLFW..."
cmake --build $GLFWBuildDir --config Release
Pop-Location

# Copy the compiled library and headers
Move-Item "$GLFWBuildDir\src\Release\glfw3.lib" "$LibDir\glfw3.lib" -Force
Move-Item "$GLFWSourceDir\include\GLFW" "$HeadersDir\GLFW" -Force

# Install Assimp
Write-Host "Installing Assimp..."
Download-Extract "https://github.com/assimp/assimp/archive/refs/tags/v5.2.5.zip" $TempDir
Move-Item "$TempDir\assimp-*\include\assimp" "$HeadersDir\assimp" -Force

# Install ImGui with docking
Write-Host "Installing ImGui..."
Download-Extract "https://github.com/ocornut/imgui/archive/refs/heads/docking.zip" $TempDir
Move-Item "$TempDir\imgui-docking" "$HeadersDir\imgui" -Force

# Install glad
Write-Host "Installing glad..."
Download-Extract "https://github.com/Dav1dde/glad/archive/refs/tags/v0.1.34.zip" $TempDir
Move-Item "$TempDir\glad-*\include\glad" "$HeadersDir\glad" -Force

# Install Khronos headers
Write-Host "Installing Khronos headers..."
Download-Extract "https://github.com/KhronosGroup/OpenGL-Registry/archive/refs/heads/main.zip" $TempDir
Move-Item "$TempDir\OpenGL-Registry-main\api\GL" "$HeadersDir\KHR" -Force

# Install stb_image
Write-Host "Installing stb_image..."
Download-Extract "https://github.com/nothings/stb/archive/refs/heads/master.zip" $TempDir
Move-Item "$TempDir\stb-master\stb_image.h" "$HeadersDir\stb_image.h" -Force

Write-Host "Installation complete! Headers are in $HeadersDir, and GLFW static library is in $LibDir."
