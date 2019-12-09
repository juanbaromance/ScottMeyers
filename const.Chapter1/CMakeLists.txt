set(ppc no)
if( ppc )
    set(CMAKE_C_COMPILER   ppc-gcc)
    set(CMAKE_CXX_COMPILER ppc-g++)
    set(tail ppc )
    set(CMAKE_CXX_FLAGS "-O3 -g")
else()
    set(tail local)
    set(CMAKE_CXX_FLAGS "-O0 -std=c++1z")
endif()

set( SOURCES chapter1.cpp.cpp chapter1.h )
add_executable(chapter1.${tail}.x chapter1.cpp)


