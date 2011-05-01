
macro(nlua_FILES name folder)
    file(GLOB sources ${TOP_SRC_DIR}/${folder}/*.cpp) 
    file(GLOB headers ${TOP_SRC_DIR}/${folder}/*.h) 
    set(${name}_src ${${name}_src} ${sources})
    set(${name}_h ${${name}_h} ${headers})
    project_source_group("${GROUP_CODE}" ${name}_src ${name}_h)
    include_directories(${CMAKE_SOURCE_DIR}/${folder})
    include_directories(${TOP_SRC_DIR}/${folder})
endmacro()

 
# folders in the msvc projects 
# mode==flat  : headers and sources not in folders 
# mode==split : standard behavior of cmake, split headers and sources 
# mode==<other values> : code is in this folder 
macro(project_source_group mode sources headers) 
    if(${mode} MATCHES "flat") 
        source_group("Source Files" Files) 
        source_group("Header Files" Files) 
        source_group("cmake" FILES CMakeLists.txt) 
    else() 
        if(NOT ${mode} MATCHES "split") 
            source_group("${mode}" FILES ${${sources}} ${${headers}}) 
        endif() 
    endif() 
endmacro()

#set(GROUP_CODE "Source Files")
set(GROUP_CODE "flat")

