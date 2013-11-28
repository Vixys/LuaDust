cmake_minimum_required(VERSION 2.8)

project("LuaDust Unit Test")

set(OUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_PATH})

set(LUA_DUST_UNIT_TEST lua_dust_test)

set(LUA_INCLUDE_PATH ${LUA_INCLUDE_PATH} CACHE STRING "Path to the lua include directory" FORCE)
set(LUA_LIB_PATH ${LUA_LIB_PATH} CACHE STRING "Path to the lua lib directory" FORCE)

set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories(
        ./include/

        ../hdr/
	
        ${LUA_INCLUDE_PATH}
)

link_directories(
		${LUA_LIB_PATH}

        ${EXECUTABLE_OUTPUT_PATH}
)

file(

        GLOB

        lua_dust_test_source_files

        ./*.cpp
)

add_executable(

        ${LUA_DUST_UNIT_TEST}

        ${lua_dust_test_source_files}

)

target_link_libraries(
        ${LUA_DUST_UNIT_TEST}
	
    	${LUA_DUST_LIB}

		lua52
)

add_custom_command(TARGET ${LUA_DUST_UNIT_TEST} POST_BUILD
                    WORKING_DIRECTORY ${OUT_PATH}
                    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/doFile_test.lua ./
                    COMMAND ${LUA_DUST_UNIT_TEST})