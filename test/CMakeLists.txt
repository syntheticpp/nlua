

nlua_files(test test)

set(tests_ignored )

foreach(_item ${tests_ignored})
    list(REMOVE_ITEM test_src ${TOP_SRC_DIR}/test/${_item}.cpp)
endforeach()


set(__TEST__ "-D__TEST__=\"${CMAKE_BINARY_DIR}/\"")
STRING(REGEX REPLACE "/" "\\\\\\\\" __TEST__ ${__TEST__}) 
add_definitions(${__TEST__})


foreach(_test ${test_src})
    get_filename_component(testname ${_test} NAME_WE)
    set(testname ${testname})
    add_executable(${testname} ${_test})
    target_link_libraries(${testname} nlua ${lua_libs})
    add_test(NAME ${testname} COMMAND ${testname})
endforeach()



