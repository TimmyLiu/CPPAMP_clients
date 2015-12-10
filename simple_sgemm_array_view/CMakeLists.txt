###############################################
# Author Timmy Liu
###############################################

cmake_minimum_required( VERSION 2.8.0 )

set(CMAKE_C_COMPILER "/opt/hcc/bin/hcc")
set(CMAKE_CXX_COMPILER "/opt/hcc/bin/hcc")

project( simple_sgemm_array_view )

#if (NOT MSVC)
#    message(FATAL_ERROR "only visual studio build is supported with CMake for now. Try build.sh for linux.")
#endif( )

if(MSVC)
if(MSVC_VERSION VERSION_LESS 1700)
    message(FATAL_ERROR "Visual Studio 11 or later is required.")
endif( )
endif( )

if(UNIX)
# let's print some useful stuff for hcc compiler
    message(STATUS "on UNIX system HCC compiler is required.")
    message(STATUS "you might want to specifiy hcc as the native C and C++ compiler.")
    message(STATUS "on UNIX system we need to include path to amp.h and link with hsaruntime")
endif( )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR} )

set( simple_sgemm_array_view_SOURCES
     ${PROJECT_SOURCE_DIR}/AMP_SGEMM_MAIN.cpp
     ${PROJECT_SOURCE_DIR}/cppAMP_sgemm.cpp
     ${PROJECT_SOURCE_DIR}/dummy_sgemm.c
     ${PROJECT_SOURCE_DIR}/error_checking.cpp
     ${PROJECT_SOURCE_DIR}/init_random.cpp
)

set( simple_sgemm_array_view_HEADERS
     ${PROJECT_SOURCE_DIR}/cppAMP_sgemm.h
     ${PROJECT_SOURCE_DIR}/dummy_sgemm.h
     ${PROJECT_SOURCE_DIR}/error_checking.h
     ${PROJECT_SOURCE_DIR}/init_random.h
)

set ( simple_sgemm_array_view_INCLUDE_DIR
     ${PROJECT_SOURCE_DIR}
)

if(UNIX)
    #set(HCC_AMP_INCLUDE_DIR "" CACHE PATH "path to AMP.h; likely in /opt/hcc/include")
    #set(HSA_RUNTIME_LIB "" CACHE FILEPATH "path to libhsa-runtime.so; likely in /opt/hsa/lib")
    find_package(HCC)
    find_package(HSA)
    set(HCC_CXX_FLAGS "-std=c++amp -stdlib=libc++")
    set(HCC_LD_FLAGS "-std=c++amp -L/opt/hcc/lib -Wl,--rpath=/opt/hcc/lib -lc++ -lc++abi -ldl -lpthread -Wl,--whole-archive -lmcwamp -Wl,--no-whole-archive")
endif( )

if(UNIX)
include_directories(
     ${simple_sgemm_array_view_INCLUDE_DIR}
     ${HCC_AMP_INCLUDE_DIR}
)
else( )
include_directories(
     ${simple_sgemm_array_view_INCLUDE_DIR}
)
endif( )

ADD_EXECUTABLE(simple_sgemm_array_view_EXE 
     ${simple_sgemm_array_view_SOURCES}
     ${simple_sgemm_array_view_HEADERS})

if(UNIX)
    target_link_libraries(simple_sgemm_array_view_EXE
                          ${HSA_RUNTIME_LIB}
                          m)
endif()

#set compiler flags for HCC
if(UNIX)
    SET ( CMAKE_CXX_FLAGS ${HCC_CXX_FLAGS} CACHE STRING "compile flags" FORCE)   
    SET ( CMAKE_EXE_LINKER_FLAGS ${HCC_LD_FLAGS} CACHE STRING "compile flags" FORCE) 
endif()
