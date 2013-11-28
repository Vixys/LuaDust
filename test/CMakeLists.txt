cmake_minimum_required(VERSION 2.8)

project("LuaDust Unit Test")

set(EXECUTABLE_OUTPUT_PATH ../bin/${CMAKE_BUILD_TYPE})

set(LUA_PATH ${LUA_PATH} CACHE STRING "Path to the lua directory" FORCE)

set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories(
        ./include/

        ../hdr/
	
        ${LUA_PATH}
)

link_directories(
		${LUA_PATH}

        ${EXECUTABLE_OUTPUT_PATH}
)

file(

        GLOB

        lua_dust_test_source_files

        ./*.cpp
)

add_executable(

        lua_dust_test

        ${lua_dust_test_source_files}

)

target_link_libraries(
        lua_dust_test
	
    	lua_dust

		lua52
)

add_custom_command(TARGET lua_dust_test POST_BUILD
                    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
                    COMMAND ${CMAKE_COMMAND} -E copy ../test/doFile_test.lua ./
                    COMMAND lua_dust_test)