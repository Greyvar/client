cmake_minimum_required(VERSION 3.10)
project(Greyvar)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY bin)
set(BUILD_SHARED_LIBS off)

find_package(PkgConfig)

include_directories(${CMAKE_SOURCE_DIR}/src/core/)

file(GLOB_RECURSE CORE_SOURCE_FILES src/core/*.cpp src/core/*.hpp)
add_library(greyvar_core ${CORE_SOURCE_FILES})

file(GLOB_RECURSE VESSEL_SOURCE_FILES src/vessel/*.cpp src/vessel/*.hpp)
add_executable(greyvar_vessel ${VESSEL_SOURCE_FILES})

message("Core source: ${CORE_SOURCE_FILES}")

if (WINDOWS)
	add_definitions(-DGREYVAR_PLATFORM_WINDOWS)
	set(PLATFORM_CXX_FLAGS "-s")

	target_include_directories(greyvar_core PUBLIC 
		/usr/x86_64-w64-mingw32/sys-root/mingw/include/freetype2
		/usr/x86_64-w64-mingw32/sys-root/mingw/include/SDL2
		./lib/SDL2_net-2.0.1/x86_64-w64-mingw32/include/
	)

    SET(CMAKE_FIND_LIBRARY_PREFIXES "lib" "")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".dll" ".dll.a" ".a" ".lib")

	find_library(LIBSDL2NET SDL2_net HINTS lib/SDL2_net-2.0.1/x86_64-w64-mingw32/lib/)

	target_link_libraries(greyvar_core mingw32 SDL2main SDL2 SDL2_image SDL2_mixer ${LIBSDL2NET} freetype m user32 gdi32 winmm)

	set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

	set_target_properties(greyvar_core PROPERTIES LINK_SEARCH_END_STATIC 1)

	set_target_properties(greyvar_vessel PROPERTIES OUTPUT_NAME "greyvar_windows")
	target_link_libraries(greyvar_vessel greyvar_core)
elseif(UNIX)
	add_definitions(-DGREYVAR_PLATFORM_LINUX)

	if (CMAKE_BUILD_TYPE MATCHES Debug) 
		set(PLATFORM_CXX_FLAGS "-fsanitize=address ")
	else()
		set(PLATFORM_CXX_FLAGS "-s ")
	endif()

	target_include_directories(greyvar_core PUBLIC /usr/include/freetype2)

	target_link_libraries(greyvar_core SDL2 SDL2_image freetype SDL2_net SDL2_mixer)

	set_target_properties(greyvar_vessel PROPERTIES OUTPUT_NAME "greyvar_linux")
	target_link_libraries(greyvar_vessel greyvar_core)
	
	file(GLOB_RECURSE TST_SOURCE_FILES tst/*.cpp tst/*.hpp)
	add_executable(greyvar_test ${TST_SOURCE_FILES})
	target_include_directories(greyvar_test PUBLIC
		src/core/
	)
	target_link_libraries(greyvar_test gtest greyvar_core)
	set_target_properties(greyvar_test PROPERTIES OUTPUT_NAME "greyvar_linux_test")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow-compatible-local -Wextra -pedantic -std=c++14 ${PLATFORM_CXX_FLAGS}") # -Weffc++

