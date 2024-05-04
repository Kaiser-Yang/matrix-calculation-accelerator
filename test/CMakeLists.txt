cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED on)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_EXTENSIONS off)

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# enable testing in cmake
enable_testing()
include(GoogleTest)

aux_source_directory(src UNIT_TEST_SOURCE)
add_executable(${PROJECT_NAME}_unit_test ${UNIT_TEST_SOURCE})
target_link_libraries(
    ${PROJECT_NAME}_unit_test
    GTest::gtest_main
    mca)
gtest_discover_tests(${PROJECT_NAME}_unit_test)

find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if (CLANG_TIDY_EXE)
    set_target_properties(${PROJECT_NAME}_unit_test PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()
