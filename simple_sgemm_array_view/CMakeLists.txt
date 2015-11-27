###############################################
# Author Timmy Liu
###############################################

cmake_minimum_required( VERSION 3.0.0 )

project( simple_sgemm_array_view )

if (NOT MSVC)
    message(FATAL_ERROR "only visual studio build is supported with CMake for now. Try build.sh for linux.")
endif( )

if(MSVC_VERSION VERSION_LESS 1700)
    message(FATAL_ERROR "Visual Studio 11 or later is required.")
endif( )
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

include_directories(
     ${simple_sgemm_array_view_INCLUDE_DIR}
)

ADD_EXECUTABLE(simple_sgemm_array_view_EXE 
     ${simple_sgemm_array_view_SOURCES}
     ${simple_sgemm_array_view_HEADERS})