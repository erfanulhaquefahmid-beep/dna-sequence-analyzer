cmake_minimum_required(VERSION 3.16)

project(dna_sequence_analyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(dna_core STATIC
    src/comparison.cpp
    src/dna_generator.cpp
    src/graph.cpp
    src/replication.cpp
    src/searching.cpp
    src/sorting.cpp
    src/test_data.cpp
    src/transformation.cpp
    src/translation.cpp
)

target_include_directories(dna_core
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

add_executable(dna_analyzer
    src/main.cpp
    src/tests.cpp
)

target_compile_definitions(dna_analyzer
    PRIVATE
        DNA_TESTS_AS_LIBRARY
)

target_link_libraries(dna_analyzer
    PRIVATE
        dna_core
)

add_executable(dna_tests
    src/tests.cpp
)

target_link_libraries(dna_tests
    PRIVATE
        dna_core
)
