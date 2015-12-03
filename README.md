This is a rather informal readme. It is more of a me-read file actually.
This is my pet project that I learn about how to use C++ AMP.

### 12/02/2015
There are two projects so far:
- simple_sgemm_array<br />
  "array" version of a simple c++ amp sgemm implementation

- simple_sgemm_array_view<br />
  "array_view" version of a simple c++ amp sgemm implementation<br />

##### Windows 10
- system set up: Haswell + FIJI
- use the CMake file to generate VS 2015 solution
- array_view project compile and run without any problem
- array project currently crashes unless I unroll the inner most for loop<br />
```
for (int k = 0; k < K; k++)
{
    localSum += alpha * gpuA[k][idx0] * gpuB[k][idx1];
}
```

 to
```
localSum += alpha * gpuA[0][idx0] * gpuB[0][idx1];
localSum += alpha * gpuA[1][idx0] * gpuB[1][idx1];
localSum += alpha * gpuA[2][idx0] * gpuB[2][idx1];
localSum += alpha * gpuA[3][idx0] * gpuB[3][idx1];
...
```
Of course this is silly.

 Another work-around uses 1-d array instead of 2-d array (and do the index math myself within the kernel). This won't crash for some reason. I intend to check it in to the repo later.

##### Linux
- system set up: Haswell + FIJI
- prerequisites: HCC (https://bitbucket.org/multicoreware/cppamp-ng-35/overview) compiler, HSA runtime, HSA driver
- use the build.sh to compile the project. 
- both projects compile and run
