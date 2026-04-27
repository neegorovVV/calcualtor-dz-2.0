cmake_minimum_required(VERSION 3.10)
project(calculator_oop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)


FetchContent_Declare( 
json

GIT_REPOSITORY https://github.com/nlohmann/json.git 

GIT_TAG v3.12.0)
FetchContent_MakeAvailable(json)

FetchContent_Declare( 
testmath

GIT_REPOSITORY https://github.com/neegorovVV/test-math.git

GIT_TAG math-lib-oop-refactoring)
FetchContent_MakeAvailable(testmath)

FetchContent_Declare( 
googletest

GIT_REPOSITORY https://github.com/google/googletest.git

GIT_TAG v1.17.0)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare( 
spdlog

GIT_REPOSITORY https://github.com/gabime/spdlog.git

GIT_TAG v1.17.0)
FetchContent_MakeAvailable(spdlog)

add_executable(calc_oop
    src/main.cpp
    src/Logger.cpp
    src/Parser.cpp
    src/Calculator.cpp
    src/Printer.cpp
    src/Runner.cpp
)

target_include_directories(calc_oop PRIVATE ${testmath_SOURCE_DIR})

target_link_libraries(calc_oop
    PRIVATE
    nlohmann_json::nlohmann_json
    spdlog::spdlog
)


enable_testing()

add_executable(tests
    tests/test_calculator.cpp
    src/Calculator.cpp
)

target_include_directories(tests PRIVATE ${testmath_SOURCE_DIR})

target_link_libraries(tests
    PRIVATE
    gtest_main
    nlohmann_json::nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(tests)
