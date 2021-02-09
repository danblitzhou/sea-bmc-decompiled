# Verify program equivalence
Verify equivalence between original C program and decompiled version using BMC in [SeaHorn](https://github.com/seahorn/seahorn).

We use a *unit proof* to verify that given two equivalent memory states `arr_a` and `arr_b`, calling original and decompiled version of `foo` on them will result in two modified but equivalent memory states. See the detail of the proof in [seahorn/jobs/foo/foo_harness.c](seahorn/jobs/foo/foo_harness.c).

## Quick start
### *Running in docker*
```bash
$ docker build -t sea-bmc-decomp -f docker/verify-c-common.Dockerfile .
$ docker run -t sea-bmc-decomp /bin/bash -c "cd build && ./verify seahorn/jobs/foo"
```
To see what other options you can use for `build/verify` script, read on.

### *Local build*
Before getting started, make sure you have `llvm-10`, `clang-10` and `clang++-10` installed.

Also install `dev10` branch of `SeaHorn` following this [guide](https://github.com/seahorn/seahorn/tree/dev10#developers-zone).

### *Building with CMake*
Create and enter a fresh build directory
```bash
$ mkdir build
$ cd build
```
1. Configure CMake
  ```bash
  $ cmake \
    -DSEA_LINK=llvm-link-10 \
    -DCMAKE_C_COMPILER=clang-10 \
    -DCMAKE_CXX_COMPILER=clang++-10 \
    -DSEAHORN_ROOT=${SEAHORN_ROOT} \
    -DENABLE_MEMCPY=ON \
    -GNinja ../
  ```
  `SEAHORN_ROOT` is the diretory containing your local SeaHorn repository.

  `ENABLE_MEMCPY` is an option for switching between `memcpy` and `bcmp` for establishing memory state equivalence as a pre-condition. We recommend leaving this option ON to avoid loop unwinding and improve performance.

2. build the project:
    ```bash
    cmake --build .
    ```
    or
    ```bash
    ninja
    ```

Now you should have a bitcode file named `build/seahorn/jobs/foo/llvm-ir/foo.ir/foo.ir.bc`;

Use executable script `verify` under the build directory to run verification.

Normal mode:
```bash
$ ./verify seahorn/jobs/foo/llvm-ir/foo.ir/foo.ir.bc
```
Counterexample mode if you need to debug
```bash
$ ./verify --cex seahorn/jobs/foo/llvm-ir/foo.ir/foo.ir.bc
```
Vacuity mode to check if all assertions can be reached
```bash
$ ./verify --vac seahorn/jobs/foo/llvm-ir/foo.ir/foo.ir.bc
```

To read more about BMC with `SeaHorn`, take a look at our case study of using it to [verify AWS C Common](https://github.com/seahorn/verify-c-common/).
