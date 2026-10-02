cmake_minimum_required(VERSION 3.16)

project(dna_sequence_analyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.[cC][pP][pP]"
    "${CMAKE_SOURCE_DIR}/src/*.[cC][cC]"
    "${CMAKE_SOURCE_DIR}/src/*.[cC][xX][xX]"
)

file(GLOB_RECURSE APP_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/include/*.[hH]"
    "${CMAKE_SOURCE_DIR}/include/*.[hH][pP][pP]"
)

if(EXISTS "${CMAKE_SOURCE_DIR}/tests" AND IS_DIRECTORY "${CMAKE_SOURCE_DIR}/tests")
    file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/tests/*.[cC][pP][pP]"
        "${CMAKE_SOURCE_DIR}/tests/*.[cC][cC]"
        "${CMAKE_SOURCE_DIR}/tests/*.[cC][xX][xX]"
    )
else()
    set(TEST_SOURCES "")
endif()

list(FILTER APP_SOURCES EXCLUDE REGEX ".*[Mm]ain\\.[cC][pP][pP]$")

if(APP_SOURCES)
    add_library(dna_core STATIC ${APP_SOURCES} ${TEST_SOURCES})
    target_include_directories(dna_core PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/tests
    )
    target_compile_definitions(dna_core PRIVATE DNA_TESTS_AS_LIBRARY)
else()
    message(FATAL_ERROR "No implementation sources were found in src/.")
endif()

file(GLOB MAIN_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*[Mm]ain*.[cC][pP][pP]"
    "${CMAKE_SOURCE_DIR}/src/*[Mm]ain*.[cC][cC]"
    "${CMAKE_SOURCE_DIR}/src/*[Mm]ain*.[cC][xX][xX]"
)

if(MAIN_SOURCES)
    add_executable(dna_analyzer ${MAIN_SOURCES})
    target_link_libraries(dna_analyzer PRIVATE dna_core)
    target_include_directories(dna_analyzer PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/tests
    )
endif()

if(TEST_SOURCES)
    add_executable(dna_tests ${TEST_SOURCES})
    target_link_libraries(dna_tests PRIVATE dna_core)
    target_include_directories(dna_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/tests
    )
endif()
