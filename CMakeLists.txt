cmake_minimum_required(VERSION 2.8)

project(LuaDust)

set(OUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

set(LIBRARY_OUTPUT_PATH ${OUT_PATH})

set(LUA_INCLUDE_PATH ${LUA_INCLUDE_PATH} CACHE STRING "Path to the lua include directory" FORCE)

set(LUA_LIB_PATH ${LUA_LIB_PATH} CACHE STRING "Path to the lua lib directory" FORCE)

LINK_DIRECTORIES(${LUA_PATH})

set(CMAKE_CXX_FLAGS "-std=c++11")

set(LUA_DUST_LIB lua_dust)
set(LUA_DUST_LIB ${LUA_DUST_LIB} PARENT_SCOPE)

set(LUA_DUST_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/hdr)
set(LUA_DUST_INCLUDE ${LUA_DUST_INCLUDE} PARENT_SCOPE)

include_directories(
        ${LUA_DUST_INCLUDE}
	
        ${LUA_INCLUDE_PATH}
)


link_directories(
	   ${LUA_LIB_PATH}
)

file(

        GLOB_RECURSE

        source_files

        src/*
)

add_library(

        ${LUA_DUST_LIB}

        SHARED

        ${source_files}

)

set_target_properties(${LUA_DUST_LIB} PROPERTIES PREFIX "")

target_link_libraries(
	${LUA_DUST_LIB}

	lua52
)

add_subdirectory(test)