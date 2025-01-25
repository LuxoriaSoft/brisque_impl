cmake_minimum_required(VERSION 3.23)
project(BRISQUEQuality)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set OpenCV_ROOT for vcpkg-installed OpenCV
if(DEFINED ENV{VCPKG_INSTALLED_DIR})
    set(OpenCV_ROOT "$ENV{VCPKG_INSTALLED_DIR}/${CMAKE_VCPKG_TARGET_TRIPLET}/share/opencv4")
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Find the OpenCV library
find_package(OpenCV REQUIRED)

# Add the executable
add_executable(brisque_quality main.cpp)

# Add the includes folder to the include directories
target_include_directories(brisque_quality PUBLIC ${CMAKE_SOURCE_DIR}/includes)

# Link the OpenCV libraries
target_link_libraries(brisque_quality ${OpenCV_LIBS})

# Optional: Add include directories for OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Set the output directory for the built executable
set_target_properties(brisque_quality PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# Suppress library conflicts
target_link_options(brisque_quality PRIVATE "/NODEFAULTLIB:library")