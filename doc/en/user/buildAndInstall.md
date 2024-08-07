# Get started
A simple process can be depicted below:

1. First, you need clone or download the repository. And enter the root directory of the repository. 
2. Use `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release` to configure `cmake`.
3. Enter the directory after argument `-B`, in this example it is `build`.
4. Use `cmake --build . -j8` to compile the project. The `-j8` means compiling with `8` threads, and
this has nothing to do with the number of threads when calculating, you can change the number if you
like.
5. Use `cmake --install . --prefix /usr` to install the library to `/usr`, you can change the
argument after `--prefix` to specify where you want to install the library.

Note that if you install the library to a directory which is not a shared library search directory,
you may need update `LD_LIBRARY_PATH` to let the linker find the library when running it. Or you can
build `mca` as a static library by adding `-Dmca_BUILD_SHARE_LIB=off` when configuring `cmake`.

# Supported options
|                                      |   |
| -                                    | - |
| <nobr>`mca_BUILD_SHARED_LIB`</nobr>  | Whether or not to build shared libraries. Default value `on` |
| <nobr>`mca_BUILD_TEST`</nobr>        | Whether or not to build unit test. Default value `off` |
| <nobr>`mca_GENERATE_COVERATE`</nobr> | Whether or not to generate code coverage report. Default value `off` |
| <nobr>`mca_BUILD_EXAMPLE`</nobr>     | Whether or not to build examples. Default value `on` |

# How to run the examples
Every `cpp` file in `example` will be compiled and generate an executable. There will be a directory
called `example` in your build directory after building and compiling. You just need run the
executable files to see the output of the examples.

[Next: `mca::Matrix`](matrix.md)

[Back to the index](index.md)
