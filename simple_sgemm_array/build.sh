export LD_LIBRARY_PATH=/opt/hsa/lib

/home/tliu/examples/hcc/bin/hcc -c error_checking.cpp -L/opt/hsa/lib -lhsa-runtime64 -lelf
/home/tliu/examples/hcc/bin/hcc -c init_random.cpp -L/opt/hsa/lib -lhsa-runtime64 -lelf
/home/tliu/examples/hcc/bin/hcc -c dummy_sgemm.c -L/opt/hsa/lib -lhsa-runtime64 -lelf
/home/tliu/examples/hcc/bin/hcc -c cppAMP_sgemm.cpp -L/opt/hsa/lib -lhsa-runtime64 -lelf
/home/tliu/examples/hcc/bin/hcc -c AMP_SGEMM_MAIN.cpp -L/opt/hsa/lib -lhsa-runtime64 -lelf
/home/tliu/examples/hcc/bin/hcc -o AMP_SGEMM_EXE AMP_SGEMM_MAIN.o error_checking.o cppAMP_sgemm.o dummy_sgemm.o init_random.o -L/opt/hsa/lib -lhsa-runtime64 -lelf
