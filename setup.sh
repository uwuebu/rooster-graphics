#!/bin/bash

# Define installation directories
RootDir="$(pwd)"
HeadersDir="$RootDir/headers"
LibDir="$RootDir/lib"
TempDir="$RootDir/temp"
BuildDir="$TempDir/build"

# Check if CMake is installed
if ! command -v cmake &> /dev/null
then
    echo "CMake is not installed. Please install CMake and try again."
    exit 1
fi

# Create directories if they don't exist
mkdir -p "$HeadersDir" "$LibDir" "$TempDir" "$BuildDir"

# Function to download and extract zip files
DownloadExtract() {
    url=$1
    destination=$2
    zipPath="$TempDir/temp.zip"
    curl -L -o "$zipPath" "$url"
    unzip -o "$zipPath" -d "$destination"
    rm -f "$zipPath"
}

# Install GLM
echo "Installing GLM..."
DownloadExtract "https://github.com/g-truc/glm/archive/refs/tags/1.0.0.zip" "$TempDir"
mv "$TempDir/glm-*/glm" "$HeadersDir/glm"

# Install GLFW and build it as a static library
echo "Installing GLFW..."
DownloadExtract "https://github.com/glfw/glfw/archive/refs/tags/3.4.zip" "$TempDir"
GLFWSourceDir="$TempDir/glfw-3.4"
GLFWBuildDir="$BuildDir/glfw"
mkdir -p "$GLFWBuildDir"

# Run CMake to generate Makefiles
echo "Configuring GLFW build..."
pushd "$GLFWBuildDir"
cmake -DBUILD_SHARED_LIBS=OFF -S "$GLFWSourceDir" -B "$GLFWBuildDir"

# Build GLFW using Make
echo "Building GLFW..."
cmake --build "$GLFWBuildDir" --config Release
popd

# Copy the compiled library and headers
mv "$GLFWBuildDir/src/Release/libglfw3.a" "$LibDir/glfw3.a"
mv "$GLFWSourceDir/include/GLFW" "$HeadersDir/GLFW"

# Install Assimp
echo "Installing Assimp..."
DownloadExtract "https://github.com/assimp/assimp/archive/refs/tags/v5.2.5.zip" "$TempDir"
mv "$TempDir/assimp-*/include/assimp" "$HeadersDir/assimp"

# Install ImGui with docking
echo "Installing ImGui..."
DownloadExtract "https://github.com/ocornut/imgui/archive/refs/heads/docking.zip" "$TempDir"
mv "$TempDir/imgui-docking" "$HeadersDir/imgui"

# Install glad
echo "Installing glad..."
DownloadExtract "https://github.com/Dav1dde/glad/archive/refs/tags/v0.1.34.zip" "$TempDir"
mv "$TempDir/glad-*/include/glad" "$HeadersDir/glad"

# Install Khronos headers
echo "Installing Khronos headers..."
DownloadExtract "https://github.com/KhronosGroup/OpenGL-Registry/archive/refs/heads/main.zip" "$TempDir"
mv "$TempDir/OpenGL-Registry-main/api/GL" "$HeadersDir/KHR"

# Install stb_image
echo "Installing stb_image..."
DownloadExtract "https://github.com/nothings/stb/archive/refs/heads/master.zip" "$TempDir"
mv "$TempDir/stb-master/stb_image.h" "$HeadersDir/stb_image.h"

echo "Installation complete! Headers are in $HeadersDir, and GLFW static library is in $LibDir."
