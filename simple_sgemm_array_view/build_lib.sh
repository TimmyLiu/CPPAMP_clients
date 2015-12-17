export LD_LIBRARY_PATH=/opt/hsa/lib

#creating libsimple_sgemm.so
#create .o file
/opt/hcc/bin/hcc `/opt/hcc/bin/clamp-config --cxxflags` -fPIC -c cppAMP_sgemm.cpp
#create .so file from .o file
/opt/hcc/bin/hcc `/opt/hcc/bin/clamp-config --ldflags --shared` -o libsimple_sgemm.so cppAMP_sgemm.o


#create the .o files for the main project
/opt/hcc/bin/hcc `/opt/hcc/bin/clamp-config --cxxflags` -c error_checking.cpp
/opt/hcc/bin/hcc `/opt/hcc/bin/clamp-config --cxxflags` -c init_random.cpp
/opt/hcc/bin/hcc -c dummy_sgemm.c
/opt/hcc/bin/hcc `/opt/hcc/bin/clamp-config --cxxflags` -c AMP_SGEMM_MAIN.cpp

#create the executable
/opt/hcc/bin/hcc `/opt/hcc/bin/clamp-config --ldflags` -o AMP_SGEMM_EXE AMP_SGEMM_MAIN.o error_checking.o dummy_sgemm.o init_random.o -L/opt/hsa/lib -lhsa-runtime64 -lelf -lm -L/home/timmy/Documents/Github/CPPAMP_clients/OnlineCPPAMP/simple_sgemm_array_view -lsimple_sgemm