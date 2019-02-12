# shared

## Abstract

Using the POSIX library functions in `<dlfcn.h>`, dynamic libraries can be
loaded and symbols linked against at runtime. Combined with a little
hand-rolled vtable trickery, this can be used to dynamically load the
implementation of a type at runtime.

## Sample output of bench_vec_wrapper

```
2019-02-12 17:05:33
Running ./bench_vec_wrapper
Run on (4 X 4000 MHz CPU s)
CPU Caches:
  L1 Data 32K (x2)
  L1 Instruction 32K (x2)
  L2 Unified 256K (x2)
  L3 Unified 4096K (x1)
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
-----------------------------------------------------------
Benchmark                    Time           CPU Iterations
-----------------------------------------------------------
bm_push_back_c              11 ns         11 ns   60805741
bm_push_back_cxx            13 ns         13 ns   50425440
bm_push_back_stdlib          4 ns          4 ns  193705113
```
