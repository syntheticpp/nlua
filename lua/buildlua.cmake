
project (LUA C)

set(LUA_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lua/src)

# the following two variables are defined for the use of packages 
# that wish to link or compile against lua
set (LUA_INCLUDE_DIRS "${LUA_SRC_DIR}")
set (LUA_LIBRARIES lua)


macro(add_prefix _list _prefix)
	set(_tmp)
	foreach(_current ${${_list}})
		set(_file ${_prefix}/${_current})
		if(LUA_COMPILED_AS_CPP)
			set_source_files_properties(${_file} PROPERTIES LANGUAGE CXX)
		endif()
		list(APPEND _tmp ${_file})
		#message( ${_prefix}/${_current})
	endforeach()
	set(${_list} ${_tmp})
endmacro()


# define the lua core source files
set (LUA_CORE_SRCS lapi.c lcode.c ldebug.c ldo.c ldump.c 
	 lfunc.c lgc.c llex.c lmem.c lobject.c lopcodes.c
	 lparser.c lstate.c lstring.c ltable.c ltm.c  lundump.c
	 lvm.c lzio.c)
add_prefix(LUA_CORE_SRCS ${LUA_SRC_DIR}/)

# define the lua lib source files
set (LUA_LIB_SRCS lauxlib.c lbaselib.c ldblib.c liolib.c
	lmathlib.c loslib.c ltablib.c lstrlib.c loadlib.c linit.c)
add_prefix(LUA_LIB_SRCS ${LUA_SRC_DIR}/)

file(GLOB LUA_LIB_H ${LUA_SRC_DIR}/*.h)

# create the library
if(WIN32)
	add_definitions(-DLUA_BUILD_AS_DLL)
	if(MSVC)
		add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	endif()
else()
	add_definitions(-DLUA_USE_LINUX)
endif()
set(LIBRARY_TYPE SHARED)

add_definitions(-DLUA_USE_APICHECK)

add_library (${lualib_name} ${LIBRARY_TYPE} ${LUA_LIB_SRCS} ${LUA_CORE_SRCS} ${LUA_LIB_H})

if(UNIX)
	target_link_libraries (${lualib_name} readline)
	if(NOT APPLE)
		target_link_libraries (${lualib_name} dl m history ncurses)
	endif()
endif()

if(NOT LUA_COMPILED_AS_CPP)
	# create the lue executable and link it to the lib
	add_executable (luaexec ${LUA_SRC_DIR}/lua.c)
	target_link_libraries (luaexec ${lualib_name})

	# name the executable lua just like the library
	set_target_properties(luaexec PROPERTIES OUTPUT_NAME ${lualib_name})
endif()

# create the luac thing (I have no clue) and link it
#add_executable (luac ${LUA_SRC_DIR}/luac.c ${LUA_SRC_DIR}/print.c)
#target_link_libraries (luac ${lualib_name})
