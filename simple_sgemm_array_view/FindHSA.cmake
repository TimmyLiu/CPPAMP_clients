###############################################
# Attempt to find HSA LIB files 
# for HCC compiler
# Author Timmy Liu
###############################################

if(NOT UNIX)
	message(FATAL_ERROR "HSA runtime only works on UNIX system.")
endif()

find_library(HSA_RUNTIME_LIB
          NAMES libhsa-runtime64.so
          HINTS 
              ${HSA_ROOT}/lib
              $ENV{HSAROOT}/lib
          PATHS
              /opt/hsa/lib
          DOC "HSA runtime filepath"
)
mark_as_advanced( HSA_RUNTIME_LIB )
