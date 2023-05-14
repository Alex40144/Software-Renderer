cmake_minimum_required (VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)

# Below line is for using C++20 standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# Our project name
project (SoftwareRenderer)
include_directories(include)

set(SOURCES main.cpp softwareRenderer.cpp)
add_executable(SoftwareRenderer ${SOURCES})

# For finding our SDL2 package!
INCLUDE(FindPkgConfig)

# Searching SDL2 package.
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

# Including our external library's directory for header files!
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

# Linking SDL2 library with our project.
target_link_libraries(SoftwareRenderer ${SDL2_LIBRARIES})