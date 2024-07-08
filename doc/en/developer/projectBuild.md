# How to build the project
Once you finish your code on your new branch, you may need to compile the code to make sure the
code can be compiled. Let me introduce you how to compile the project:

1. Make sure you are in the root directory of the repository.
2. Run
`cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -Dmca_BUILD_TEST=on -Dmca_GENERATE_COVERAGE=off`.
`CMAKE_BUILD_TYPE` is to control the building version. `mca_BUILD_TESTS` is to control whether or
not to build unit tests. `mca_GENERATE_COVERAGE` is to control whether or not to generate code
coverage reports. Mostly, you needn't update those variables.
3. Run `cd build && cmake --build . -j16`, you can update `16` with any other positive number to
specify how many threads you want to use when building the project (You'd better make sure it not
exceed the number of your `cpu` cores or `cpu` super-threads). If there is no any error, your code
can be compiled successfully.

If you want the build process same with `git action`s, you need make sure `clang-tidy` is available
on your computer. If you use `UNIX-like` system, you can use `sudo apt-get install clang-tidy` to
install `clang-tidy`. If you don't install `clang-tidy` the code you write may be compiled
successfully locally, but may not pass the `git action`s.

# All the options for cmake
|                                      |   |
| -                                    | - |
| <nobr>`mca_BUILD_SHARED_LIB`</nobr>  | Whether or not to build shared libraries. Default value `on` |
| <nobr>`mca_BUILD_TEST`</nobr>        | Whether or not to build unit test. Default value `off` |
| <nobr>`mca_GENERATE_COVERATE`</nobr> | Whether or not to generate code coverage report. Default value `off` |
| <nobr>`mca_BUILD_EXAMPLE`</nobr>     | Whether or not to build examples. Default value `on` |

# Write and run the unit test
Although you compile your code successfully, you should be aware of that the code which is
compiled successfully may not work properly. So you need write unit tests for the every function you
write. So you need create a file which is related with your new code. The filename is usually the
origin base filename followed by `_test.cpp`. If there have been already one, you just need append
your unit tests code. If you finish writing unit tests, you can re-build the project through step
`1-3` above. And change your directory to `build/test` (after building successfully), then run
`ctest --output-on-failure`, this will start running all the test units. If all the tests pass, your
code may be OK. If there are some tests failed, you need check the code you write (both test code
and the source code), and update them to pass all the tests.

# Write examples and documents for public API
All the public (used by users) functions or methods you add for the project should be documented.
You should update the document `doc/en/user/index.md` to add a new index, and then add a new file
related to the new index. If there already is a file for file containing the new API, you just need
update the existed file. Every example will be built and compiled to an executable in the
`example` directory of your build directory, and you can execute them to check the output.

# How to generate code coverage report locally
You may want to see the code coverage locally. You can do those below to generate the `html` files
for code coverage report after building and compiling (make sure `mca_BUILD_TEST` and
`mca_GENERATE_COVERATE` are `on`):

1. Change your directory to `build/test`.
2. Run `./mca_unit_test`.
3. Change your directory to `build`.
4. Run `lcov --capture --directory . --output-file coverage.info` to generate report.
5. Run `genhtml --output-directory coverage_report coverage.info` to generate `html` files.
6. Open the `index.html` in the `build/coverage_report` directory to see the code coverage report.

[Back to `How to write my code`](codeWrite.md)

[Next: `How to submit my code`](codeubmit.md)

[Back to the index](index.md)
