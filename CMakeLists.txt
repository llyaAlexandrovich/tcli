cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

include(FetchContent)


# Default values.
set(TCLI_VERSION "1.0.0")           # Set program version.
set(CMAKE_CXX_STANDARD "23")        # Set cxx version for cmake build.
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Force to have required cxx version.



# Add default target.
add_executable(TCli src/main.cpp)



project(TCli VERSION ${TCLI_VERSION} LANGUAGES CXX) # Project basis.



# Includes.
target_include_directories(TCli PRIVATE include)
target_include_directories(TCli PRIVATE src)



# Libs.
link_directories(/lib)



# Fetchs.
FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
    GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)



# Linking.
target_link_libraries(TCli PRIVATE tdcore.lib)
target_link_libraries(TCli PRIVATE 
    ftxui::component
    ftxui::dom
    ftxui::screen
)
