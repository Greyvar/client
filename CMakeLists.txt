cmake_minimum_required(VERSION 3.10)
project(Greyvar)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(BUILD_SHARED_LIBS off)

find_package(PkgConfig)

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB SOURCE_FILES src/*.cpp src/*.hpp)
add_executable(greyvar ${SOURCE_FILES})

message("Source: ${SOURCE_FILES}")

set(CMAKE_VERBOSE_MAKEFILE on)

if (WINDOWS)
	message("Windows Build")

	target_include_directories(greyvar PUBLIC 
		/usr/x86_64-w64-mingw32/sys-root/mingw/include/freetype2
		/usr/x86_64-w64-mingw32/sys-root/mingw/include/SDL2
		./lib/SDL2_net-2.0.1/x86_64-w64-mingw32/include/
	)

	find_library(LIBSDL2NET SDL2_net HINTS lib/SDL2_net-2.0.1/x86_64-w64-mingw32/lib/)

	target_link_libraries(greyvar mingw32 SDL2main SDL2 SDL2_image ${LIBSDL2NET} freetype m user32 gdi32 winmm)
	set_target_properties(greyvar PROPERTIES LINK_SEARCH_END_STATIC 1)
else()
	message("Linux Build")

	target_include_directories(greyvar PUBLIC /usr/include/freetype2)

	set_target_properties(greyvar PROPERTIES OUTPUT_NAME "greyvar_linux")
	target_link_libraries(greyvar SDL2 SDL2_image freetype SDL2_net)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11")

