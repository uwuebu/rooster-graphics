cmake_minimum_required(VERSION 3.20)
project(PersonalGraphicsEngineReworked)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define directories
set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(HEADERS_DIR ${ROOT_DIR}/headers)
set(LIB_DIR ${ROOT_DIR}/lib)
set(SOURCE_DIR ${ROOT_DIR}/source)

# Include directories
include_directories(${HEADERS_DIR})
include_directories(${HEADERS_DIR}/imgui)
include_directories(${HEADERS_DIR}/imgui/backends)

# Add ImGui source files
file(GLOB IMGUI_SOURCES
    ${HEADERS_DIR}/imgui/*.cpp
    ${HEADERS_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${HEADERS_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

# Add source files
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cc ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.h)

# Remove duplicate source files
list(REMOVE_DUPLICATES SOURCES)

# Add executable
add_executable(PersonalGraphicsEngineReworked ${SOURCES} ${IMGUI_SOURCES})

# Link libraries
if (WIN32)
    target_link_libraries(PersonalGraphicsEngineReworked ${LIB_DIR}/glfw3.lib opengl32.lib)
elseif (UNIX)
    target_link_libraries(PersonalGraphicsEngineReworked ${LIB_DIR}/glfw3.lib GL)
endif()

# Add glad
add_library(glad ${HEADERS_DIR}/glad/glad.c)
target_link_libraries(PersonalGraphicsEngineReworked glad)

# Add other dependencies as needed
# target_link_libraries(PersonalGraphicsEngineReworked ${LIB_DIR}/other_library.lib)
