cmake_minimum_required(VERSION 4.2)


set(TCLI_VERSION "1.0.0")           # Set program version.
set(CMAKE_CXX_STANDARD "23")        # Set cxx version for cmake build.
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Force to have required cxx version.


s
project(TCli VERSION ${TCLI_VERSION} LANGUAGES CXX) # Project basis.



# Subdirectories.
add_subdirectory(src)
add_subdirectory(src/fs)
add_subdirectory(src/config)
add_subdirectory(src/helper)
add_subdirectory(src/security)
add_subdirectory(src/render)
add_subdirectory(src/auth)



# Includes.
include_directories(/include)



# Libs.
link_directories(/lib)



# Add default target.
add_executable(tcli main.cpp)



# Linking.
target_link_libraries(tcli libcrypto.lib)
target_link_libraries(tcli libfmt.a)
target_link_libraries(tcli libspdlog.a)
