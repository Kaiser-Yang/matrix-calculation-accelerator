cmake_minimum_required(VERSION 3.14)

project(mca)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

option(mca_BUILD_SHARE_LIB "Build shared libraries rather than static libraries" on)
option(mca_BUILD_TEST "Whether or not to build unit test" on)

aux_source_directory(src mca_SOURCE)
set(LIBRARY_OUTPUT_PATH lib)
if (mca_BUILD_SHARE_LIB)
    add_library(mca SHARED ${mca_SOURCE})
else()
    add_library(mca STATIC ${mca_SOURCE})
endif()

target_include_directories(mca PUBLIC ${PROJECT_SOURCE_DIR}/src/include)

find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if (CLANG_TIDY_EXE)
    set_target_properties(mca PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()

if (mca_BUILD_TEST)
    add_subdirectory(test)
endif()
