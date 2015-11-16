project (DECIMATION)
cmake_minimum_required(VERSION 3.3)

file(GLOB_RECURSE PCDec_SOURCES "src/*.cpp")
file(GLOB_RECURSE PCDec_HEADERS "src/*.h")

set (PCDec_INCLUDE_DIRS "")
foreach (_headerFile ${Foo_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND PCDec_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES PCDec_INCLUDE_DIRS)


# set paths (only needed on windows)
#if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
#    #SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
#    SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}  -w -Wl,-subsystem,windows -lmingw32" )
#endif()

#-Ic:/devcpp/SDL2/i686-w64-mingw32/include -Lc:/devcpp/SDL2/i686-w64-mingw32/lib

 #just flag setting if needed
#SET(GCC_COVERAGE_COMPILE_FLAGS "-mwindows")
#SET(GCC_COVERAGE_LINK_FLAGS    "")
#
#SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
#SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )


include_directories(${PCDec_INCLUDE_DIRS})
add_executable (decimate ${PCDec_SOURCES})