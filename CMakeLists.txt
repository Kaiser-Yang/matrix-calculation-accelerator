cmake_minimum_required(VERSION 3.14)

project(mca)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED on)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_EXTENSIONS off)

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

option(MCA_BUILD_SHARE_LIB "Build shared libraries rather than static libraries" on)
option(MCA_BUILD_TEST "Whether or not to build unit test" on)

aux_source_directory(src MCA_SOURCE)
aux_source_directory(src/include MCA_SOURCE)
aux_source_directory(src/single_thread MCA_SOURCE)
set(LIBRARY_OUTPUT_PATH lib)
if (MCA_BUILD_SHARE_LIB)
    add_library(mca SHARED ${MCA_SOURCE})
else()
    add_library(mca STATIC ${MCA_SOURCE})
endif()

target_include_directories(mca INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(mca PRIVATE ${PROJECT_SOURCE_DIR}/src/include)

if ((NOT WIN32) AND CMAKE_EXPORT_COMPILE_COMMANDS)
    add_custom_command(
        TARGET mca
        PRE_BUILD
        COMMAND
        ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR})
endif()

find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if (CLANG_TIDY_EXE)
    set_target_properties(mca PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()

if (MCA_BUILD_TEST)
    add_subdirectory(test)
endif()
