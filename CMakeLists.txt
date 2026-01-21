cmake_minimum_required(VERSION 4.2)


set(TCLI_VERSION "1.0.0")           # Set program version.
set(CMAKE_CXX_STANDARD "23")        # Set cxx version for cmake build.
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Force to have required cxx version.


project(TCli VERSION ${TCLI_VERSION} LANGUAGES CXX) # Project basis.


# Subdirectories.
add_subdirectory(src)
add_subdirectory(src/fs)
add_subdirectory(src/config)


# Includes.
include_directories(/thirdparty/include)
include_directories(/include)



# Add default target.
add_executable(tcli main.cpp)
