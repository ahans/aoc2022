cmake_minimum_required(VERSION 3.16)

project(aoc2022 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)

add_compile_options(-Wall -Wextra -O3 -march=native)

include(FetchContent)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 9.1.0
)

FetchContent_Declare(vectorclass
  GIT_REPOSITORY https://github.com/vectorclass/version2.git
  GIT_TAG v2.02.00
)

FetchContent_MakeAvailable(fmt vectorclass)

include_directories(${vectorclass_SOURCE_DIR})

add_executable(
  main
  common.cc
  main.cc
  days/day01.cc
  days/day02.cc
  days/day03.cc
  days/day04.cc
  days/day05.cc
  days/day06.cc
  days/day07.cc
  days/day08.cc
  days/day10.cc
  days/day11.cc
  days/day12.cc
)
target_compile_features(main PUBLIC cxx_std_17)
target_link_libraries(main PRIVATE fmt::fmt)