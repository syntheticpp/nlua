

nlua_files(nlua include/nlua)
nlua_files(details include/nlua/details)
nlua_files(nlua src)


set(ignore )

foreach(_item ${ignore})
	list(REMOVE_ITEM nlua_src ${TOP_SRC_DIR}/src/${_item}.cpp)
	list(REMOVE_ITEM nlua_h ${TOP_SRC_DIR}/include/nlua/${_item}.h)
endforeach()

set(LIB_TYPE SHARED)
if(${LIB_TYPE} MATCHES "SHARED")
	if(WIN32)
		add_definitions(-DNLUA_MAKE_DLL)
	endif()
endif()

add_library(nlua ${LIB_TYPE} ${nlua_src} ${nlua_h} ${details_h})
source_group(details FILES ${details_h})
target_link_libraries(nlua ${lua_libs})

install(TARGETS nlua DESTINATION lib)
install(DIRECTORY ${TOP_SRC_DIR}/include DESTINATION .)
