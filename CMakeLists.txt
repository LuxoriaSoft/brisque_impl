cmake_minimum_required(VERSION 3.23)
project(BRISQUEQuality)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable MSVC runtime selection for Windows builds
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Set OpenCV_ROOT if vcpkg is being used
if(DEFINED ENV{VCPKG_INSTALLED_DIR})
    set(OpenCV_DIR "$ENV{VCPKG_INSTALLED_DIR}/${CMAKE_VCPKG_TARGET_TRIPLET}/share/opencv4")
endif()

# Find OpenCV
find_package(OpenCV REQUIRED)

# Source files
set(SOURCES
    BrisqueAlgorithm.cpp
    BrisqueInterop.cpp
)

# Add the library (shared by default)
add_library(brisque_quality SHARED ${SOURCES})

# Include directories
target_include_directories(brisque_quality
    PUBLIC
        ${CMAKE_SOURCE_DIR}  # Include current project directory
        ${OpenCV_INCLUDE_DIRS}
)

# Link the OpenCV libraries
target_link_libraries(brisque_quality
    PRIVATE
        ${OpenCV_LIBS}
)

# Set output directories for shared library
set_target_properties(brisque_quality PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

if(MSVC)
    target_link_options(brisque_quality PRIVATE "/NODEFAULTLIB:library")
endif()
