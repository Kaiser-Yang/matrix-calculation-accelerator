cmake_minimum_required(VERSION 3.14)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(unit_test)
    message(FATAL_ERROR "You can not build this project as a main project")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL
    https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# enable testing in cmake
enable_testing()
include(GoogleTest)

aux_source_directory(src ${PROJECT_NAME}_unit_test_SOURCE)
add_executable(${PROJECT_NAME}_unit_test ${${PROJECT_NAME}_unit_test_SOURCE})
target_link_libraries(
    ${PROJECT_NAME}_unit_test
    PRIVATE
    GTest::gtest_main
    mca)

# In windows when using VS, this cannot find the share lib
# so we just update the working directory
# if your config type is different with ${CMAKE_BUILD_TYPE}
# you may need copy the libraries manually
# or update the environment PATH to find where the shared lib is
# if you build a static lib, this can be ignored
if (mca_BUILD_SHARE_LIB AND WIN32 AND (CMAKE_GENERATOR MATCHES "Visual Studio"))
    gtest_discover_tests(
        ${PROJECT_NAME}_unit_test
        WORKING_DIRECTORY
        ${CMAKE_BINARY_DIR}/${LIBRARY_OUTPUT_PATH}/${CMAKE_BUILD_TYPE})
else()
    gtest_discover_tests(${PROJECT_NAME}_unit_test)
endif()

find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if (CLANG_TIDY_EXE)
    set_target_properties(${PROJECT_NAME}_unit_test PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()
