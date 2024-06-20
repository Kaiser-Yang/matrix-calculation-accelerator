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
option(mca_BUILD_TEST "Whether or not to build unit test" off)
option(mca_GENERATE_COVERAGE "Whether or not to generate codes coverage report" off)
option(mca_BUILD_EXAMPLE "Whether or not to build examples" on)

if (mca_GENERATE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

aux_source_directory(src mca_SOURCE)

set(LIBRARY_OUTPUT_PATH lib)
if (mca_BUILD_SHARE_LIB)
    add_library(mca SHARED ${mca_SOURCE})
else()
    add_library(mca STATIC ${mca_SOURCE})
endif()

install(TARGETS mca DESTINATION lib)
install(DIRECTORY src/include/mca DESTINATION include)

find_package(Threads REQUIRED)
target_link_libraries(mca PUBLIC Threads::Threads)
# when built as a sub directory, epxort mca_LINK_LIB
if(NOT CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(mca_LINK_LIB ${CMAKE_THREAD_LIBS_INIT} PARENT_SCOPE)
endif()

target_include_directories(mca PUBLIC ${PROJECT_SOURCE_DIR}/src/include)

find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if (CLANG_TIDY_EXE)
    set_target_properties(mca PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()

if (mca_BUILD_TEST)
    add_subdirectory(test)
endif()

if (mca_BUILD_EXAMPLE)
    aux_source_directory(example mca_EXAMPLE_SOURCE)
    foreach(SINGLE_EXAMPLE_SRC ${mca_EXAMPLE_SOURCE})
        get_filename_component(SINGLE_EXAMPLE_EXE ${SINGLE_EXAMPLE_SRC} NAME_WE)
        add_executable(${SINGLE_EXAMPLE_EXE} ${SINGLE_EXAMPLE_SRC})
        target_link_libraries(${SINGLE_EXAMPLE_EXE} PRIVATE mca)
        target_include_directories(
            ${SINGLE_EXAMPLE_EXE}
            PRIVATE
            ${PROJECT_SOURCE_DIR}/src/include
            ${PROJECT_SOURCE_DIR}/example/include)
        set_target_properties(
            ${SINGLE_EXAMPLE_EXE}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY
            "${CMAKE_BINARY_DIR}/example")
        if (CLANG_TIDY_EXE)
            set_target_properties(
                ${SINGLE_EXAMPLE_EXE}
                PROPERTIES
                CXX_CLANG_TIDY
                "${CLANG_TIDY_EXE}")
        endif()
    endforeach()
endif()
