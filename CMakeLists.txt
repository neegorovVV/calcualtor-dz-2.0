cmake_minimum_required(VERSION 3.10)
project(calculator_oop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")




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
    src/Calc_structs/Logger.cpp
    src/Calc_structs/Parser.cpp
    src/Calc_structs/Calculator.cpp
    src/Calc_structs/Printer.cpp
    src/Calc_structs/Runner.cpp
    src/SQL/Connection_and_result.cpp
    src/cache_containers/cache_container.cpp
)

target_include_directories(calc_oop PRIVATE /usr/include/postgresql)
target_link_libraries(calc_oop PRIVATE pq)

target_include_directories(calc_oop PRIVATE 
    src/Calc_structs
    src/SQL
    src/cache_containers
    /usr/include/postgresql
)

find_package(PostgreSQL REQUIRED)
   target_link_libraries(calc_oop PRIVATE ${PostgreSQL_LIBRARIES})
   target_include_directories(calc_oop PRIVATE ${PostgreSQL_INCLUDE_DIRECTORIES})


target_include_directories(calc_oop PRIVATE ${testmath_SOURCE_DIR})

target_link_libraries(calc_oop
    PRIVATE
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    pq
)


enable_testing()

add_executable(tests
    tests/test_calculator.cpp
    src/Calc_structs/Calculator.cpp  
)

target_include_directories(tests 
PRIVATE 
src/Calc_structs
 ${testmath_SOURCE_DIR})

target_link_libraries(tests
    PRIVATE
    gtest_main
    nlohmann_json::nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(tests)

add_test(NAME tests_valgrind
    COMMAND valgrind --leak-check=full --error-exitcode=1 $<TARGET_FILE:tests>
)
