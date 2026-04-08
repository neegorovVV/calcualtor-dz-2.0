set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_minimum_required(VERSION 3.10)
project(Calculator)

include(FetchContent)


FetchContent_Declare(
    mathlib
    GIT_REPOSITORY https://github.com/neegorovVV/test-math.git
    GIT_TAG main
)

FetchContent_MakeAvailable(mathlib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(calc main.cpp)


target_include_directories(calc PRIVATE ${mathlib_SOURCE_DIR})

install(TARGETS calc DESTINATION bin)

# clang-format
find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
    add_custom_target(
        format
        COMMAND ${CLANG_FORMAT} -i ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
        COMMENT "Formatting code with clang-format"
    )
endif()

# clang-tidy
find_program(CLANG_TIDY clang-tidy)
if(CLANG_TIDY)
    add_custom_target(
        tidy
        COMMAND ${CLANG_TIDY} ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp -- -std=c++17
        COMMENT "Checking code with clang-tidy"
    )
endif()