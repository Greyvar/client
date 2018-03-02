cmake_minimum_required(VERSION 2.8)
project(Greyvar)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(BUILD_SHARED_LIBS off)

include(FindPkgConfig)
find_library(SDL2 sdl2.a SDL2_image)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(MINGW64 required mingw64)

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB SOURCE_FILES src/*.cpp src/*.hpp)
add_executable(greyvar ${SOURCE_FILES})

message("Source: ${SOURCE_FILES}")

message("SDL2: ${SDL2_LIBRARIES}")
message("MINGW64: ${MINGW32_LIBRARIES}")

set(CMAKE_VERBOSE_MAKEFILE on)

if (WINDOWS)
	message("Windows Build")

#	set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -lSDL2main -lSDL2 -static -lSDL2_image")

	target_link_libraries(greyvar mingw32 SDL2main SDL2 SDL2_image m user32 gdi32 winmm)
	set_target_properties(greyvar PROPERTIES LINK_SEARCH_END_STATIC 1)
else()
	message("Linux Build")

	set_target_properties(greyvar PROPERTIES OUTPUT_NAME "greyvar_linux")
	target_link_libraries(greyvar ${SDL2_LIBRARIES} SDL2_image)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11")

