cmake_minimum_required(VERSION 2.8.12)
project(sudoku)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Tesseract 4)
if (NOT Tesseract_FOUND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(Tesseract REQUIRED IMPORTED_TARGET GLOBAL tesseract lept)
    add_library(Tesseract::libtesseract ALIAS PkgConfig::Tesseract)
endif ()
include_directories(src)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

################################
# Unit Tests
################################
# Add test cpp file
enable_testing()
set(DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")
add_executable( parser_test test/parser_test.cc )
target_link_libraries(parser_test gtest gtest_main gmock_main stdc++fs)
add_test( parser_test parser_test)
set_property(TARGET parser_test PROPERTY CXX_STANDARD 17)
# set_tests_properties(parser_test PROPERTIES
#                     ENVIRONMENT DATA_DIR=xxxx
#                     RANDOM_PROP 3)
# set_property(TARGET parser_test APPEND PROPERTY ENVIRONMENT DATA_DIR=xxx)

add_executable( sudoku_test test/sudoku_test.cc )
target_link_libraries(sudoku_test gtest gtest_main gmock_main stdc++fs)
add_test( sudoku_test sudoku_test)
set_property(TARGET sudoku_test PROPERTY CXX_STANDARD 17)

add_executable(backtracking_solver src/backtracking_solver.cc )
target_link_libraries(backtracking_solver stdc++fs)
set_property(TARGET backtracking_solver PROPERTY CXX_STANDARD 17)

add_executable(test_ocr test/ocr/test_ocr.cc )
target_link_libraries(test_ocr ${OpenCV_LIBS} Tesseract::libtesseract stdc++fs gtest gtest_main)
add_test( test_ocr test_ocr)
set_property(TARGET test_ocr PROPERTY CXX_STANDARD 17)
