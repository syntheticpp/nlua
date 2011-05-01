project(nlua)

cmake_minimum_required(VERSION 2.6.4)

include(nluaMacros.cmake)

set(TOP_SRC_DIR ${CMAKE_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin) 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib) 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib) 


if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	set(CMAKE_DEBUG_POSTFIX)
	if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
		set(CMAKE_INSTALL_PREFIX INSTALLED CACHE PATH "nlua default install path" FORCE)
	endif()
else()
	#add_definitions(-D__GXX_EXPERIMENTAL_CXX0X__)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

add_subdirectory(lua)

include_directories(${lua_includes})
add_definitions(${lua_definitions})

include_directories(${TOP_SRC_DIR}/include)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
