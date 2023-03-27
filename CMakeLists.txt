cmake_minimum_required(VERSION 3.0.0)

# add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
# add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
# add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>")
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(hello_sdl2_easytab VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(SDL2 CONFIG REQUIRED)
# find_package(unofficial-sqlite3 CONFIG REQUIRED)

add_executable(hello_sdl2_easytab main.cpp)

target_link_libraries(hello_sdl2_easytab PRIVATE
    SDL2::SDL2 SDL2::SDL2main) #SDL2::SDL2-static
#unofficial::sqlite3::sqlite3

# cmake .. "-DCMAKE_TOOLCHAIN_FILE=D:/src/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows"
