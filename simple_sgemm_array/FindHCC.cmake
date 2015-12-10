###############################################
# Attempt to find include dir 
# for HCC compiler
# Author Timmy Liu
###############################################

if(NOT UNIX)
	message(FATAL_ERROR "HCC compiler only works on UNIX system.")
endif()

find_path(HCC_AMP_INCLUDE_DIR
          NAMES amp.h
          HINTS 
              ${HCC_ROOT}/include
              $ENV{HCCROOT}/include
          PATHS
              /opt/hcc/include
          DOC "HCC AMP head file path"
)
mark_as_advanced( HCC_AMP_INCLUDE_DIR )


