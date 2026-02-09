cmake_minimum_required(VERSION 3.12 FATAL_ERROR)


# Default values.
set(TCLI_VERSION "1.0.0")           # Set program version.
set(CMAKE_CXX_STANDARD "23")        # Set cxx version for cmake build.
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Force to have required cxx version.



project(TCli VERSION ${TCLI_VERSION} LANGUAGES CXX) # Project basis.



# Subdirectories.
add_subdirectory(src)
add_subdirectory(src/helper)
add_subdirectory(src/render)
add_subdirectory(src/localization)
add_subdirectory(src/tdhelper)



# Includes.
include_directories(/include)



# Libs.
link_directories(/lib)



# Add default target.
add_executable(tcli main.cpp)



# Linking.
target_link_libraries(tcli PRIVATE libcrypto.lib)
target_link_libraries(tcli PRIVATE libfmt.a)
target_link_libraries(tcli PRIVATE libspdlog.a)
target_link_libraries(YourTarget PRIVATE Td::TdStatic)
