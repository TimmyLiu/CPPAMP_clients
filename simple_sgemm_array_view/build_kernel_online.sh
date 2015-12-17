export LD_LIBRARY_PATH=/opt/hsa/lib

#creating libsimple_sgemm.so
#create .o file
/opt/hcc/bin/hcc `/opt/hcc/bin/clamp-config --cxxflags` -fPIC -c cppAMP_sgemm.cpp
#create .so file from .o file
/opt/hcc/bin/hcc `/opt/hcc/bin/clamp-config --ldflags --shared` -o libsimple_sgemm.so cppAMP_sgemm.o


