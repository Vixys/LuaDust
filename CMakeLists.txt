cmake_minimum_required(VERSION 2.8)

project(LuaDust)

if(NOT DEFINED OUT_PATH)
    set(OUT_PATH bin/${CMAKE_BUILD_TYPE})
endif(NOT DEFINED OUT_PATH)

set(LIBRARY_OUTPUT_PATH ${OUT_PATH})

set(LUA_PATH ${LUA_PATH} CACHE STRING "Path to the lua directory" FORCE)

LINK_DIRECTORIES(${LUA_PATH})

set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories(
        hdr/
	
        ${LUA_PATH}
)

link_directories(
	   ${LUA_PATH}
)

file(

        GLOB_RECURSE

        source_files

        src/*
)

add_library(

        lua_dust

        SHARED

        ${source_files}

)

target_link_libraries(
	lua_dust

	lua52
)

add_subdirectory(test)