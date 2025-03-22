#!/bin/bash

set -e

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

# Check if curl is installed
if ! command -v curl &> /dev/null
then
    echo "curl is not installed. Please install curl and try again."
    exit 1
fi

# Check if necessary development packages are installed
required_packages=("wayland-scanner" "pkg-config" "x11" "xkbcommon" "xrandr" "xinerama" "xcursor" "xi" "gl")
missing_packages=()
for pkg in "${required_packages[@]}"; do
    if ! pkg-config --exists "$pkg"; then
        missing_packages+=("$pkg")
    fi
done

if [ ${#missing_packages[@]} -ne 0 ]; then
    echo "The following development libraries are not installed:"
    for pkg in "${missing_packages[@]}"; do
        echo "  - $pkg"
    done
    echo "Please install the missing libraries and try again."
    exit 1
fi

# Alternatively, you can install all required packages at once using your package manager.
# For example, on Ubuntu/Debian:
# sudo apt-get install cmake curl wayland-scanner pkg-config libx11-dev libxkbcommon-dev libxrandr-dev libxinerama-dev libxcursor-dev libgl-dev

# Clear directories if they exist
rm -rf "$HeadersDir" "$LibDir" "$TempDir" "$BuildDir"

# Create directories if they don't exist
mkdir -p "$HeadersDir" "$LibDir" "$TempDir" "$BuildDir"

# Add a placeholder file to the build directory
touch "$BuildDir/.placeholder"

# Function to download and extract zip files
DownloadExtract() {
    url=$1
    destination=$2
    zipPath="$TempDir/temp.zip"
    curl -L -o "$zipPath" "$url"
    unzip -o "$zipPath" -d "$TempDir"
    extractedDir=$(find "$TempDir" -mindepth 1 -maxdepth 1 -type d | head -n 1)
    mkdir -p "$destination"
    rsync -a "$extractedDir/" "$destination"
    rm -rf "$extractedDir"
    rm -f "$zipPath"
}

# Install GLM
echo "Installing GLM..."
DownloadExtract "https://github.com/g-truc/glm/archive/refs/tags/1.0.0.zip" "$TempDir/glm"
rsync -a "$TempDir/glm/glm/" "$HeadersDir/glm"

# Install GLFW and build it as a static library
echo "Installing GLFW..."
DownloadExtract "https://github.com/glfw/glfw/archive/refs/tags/3.4.zip" "$TempDir/glfw"
GLFWSourceDir="$TempDir/glfw"
GLFWBuildDir="$BuildDir/glfw"
mkdir -p "$GLFWBuildDir"

# Run CMake to generate Makefiles
echo "Configuring GLFW build..."
pushd "$GLFWBuildDir"
cmake -DBUILD_SHARED_LIBS=OFF -DCMAKE_C_FLAGS="-static" -S "$GLFWSourceDir" -B "$GLFWBuildDir"

# Build GLFW using Make
echo "Building GLFW..."
cmake --build "$GLFWBuildDir" --config Release
popd

# Copy the compiled library and headers
compiledLibPath=$(find "$GLFWBuildDir/src" -name "libglfw3.a" | head -n 1)
if [ -z "$compiledLibPath" ]; then
    echo "Failed to find the compiled GLFW library."
    exit 1
fi
rsync -a "$compiledLibPath" "$LibDir/glfw3.lib"
rsync -a "$GLFWSourceDir/include/GLFW/" "$HeadersDir/GLFW"

# Delete the build directory
rm -rf "$BuildDir"

# Install ImGui with docking
echo "Installing ImGui..."
DownloadExtract "https://github.com/ocornut/imgui/archive/refs/heads/docking.zip" "$TempDir/imgui"
imguiDir=$(find "$TempDir" -type d -name "imgui-docking" | head -n 1)
if [ -z "$imguiDir" ]; then
    echo "Failed to find the ImGui directory."
    exit 1
fi
rsync -a "$imguiDir/" "$HeadersDir/imgui/"

# FIGURE OUT GLAD INSTALLATION LATER

# Install stb_image
echo "Installing stb_image..."
DownloadExtract "https://github.com/nothings/stb/archive/refs/heads/master.zip" "$TempDir/stb"
stbHeaderPath=$(find "$TempDir/stb-master" -type f -name "stb_image.h" | head -n 1)
if [ -z "$stbHeaderPath" ]; then
    echo "Failed to find the stb_image.h file."
    exit 1
fi
rsync -a "$stbHeaderPath" "$HeadersDir"

# Install Assimp
echo "Installing Assimp..."
DownloadExtract "https://github.com/assimp/assimp/archive/refs/tags/v5.2.5.zip" "$TempDir/assimp"
assimpDir=$(find "$TempDir" -type d -name "assimp*" | head -n 1)
assimpIncludeDir="$assimpDir/include"
if [ ! -d "$assimpIncludeDir" ]; then
    echo "Failed to find the Assimp include directory."
    exit 1
fi
rsync -a "$assimpIncludeDir/" "$HeadersDir/assimp/"

echo "Installation complete! Headers are in $HeadersDir, and GLFW static library is in $LibDir."
