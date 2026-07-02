cmake_minimum_required(VERSION 3.10)
project(calculator_oop)

find_package(Boost REQUIRED COMPONENTS system)
find_package(PostgreSQL REQUIRED)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)


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
    src/TCP_server/TCP_server.cpp
    src/TCP_server/Signal_thread.cpp
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


   target_link_libraries(calc_oop PRIVATE ${PostgreSQL_LIBRARIES})
   target_include_directories(calc_oop PRIVATE ${PostgreSQL_INCLUDE_DIRECTORIES})


target_include_directories(calc_oop PRIVATE ${testmath_SOURCE_DIR})

target_link_libraries(calc_oop
    PRIVATE
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    Boost::system
    pq
)


enable_testing()

add_executable(tests
    tests/test_calculator.cpp
    tests/test_client.cpp
    src/Calc_structs/Calculator.cpp
    src/Calc_structs/Parser.cpp
    src/Calc_structs/Runner.cpp
    src/Calc_structs/Printer.cpp
    src/Calc_structs/Logger.cpp
    src/TCP_server/TCP_server.cpp
    src/SQL/Connection_and_result.cpp
    src/cache_containers/cache_container.cpp
)


target_include_directories(tests 
PRIVATE 
    src/Calc_structs
    src/SQL                     
    src/cache_containers
    src/TCP_server
    ${testmath_SOURCE_DIR}
    /usr/include/postgresql
    ${CMAKE_CURRENT_SOURCE_DIR}/tests 
    ${spdlog_SOURCE_DIR}/include
)

target_link_libraries(tests
    PRIVATE
    gtest_main
    nlohmann_json::nlohmann_json
    Boost::system
    pq
    ${PostgreSQL_LIBRARIES} 
    spdlog::spdlog
)

include(GoogleTest)
gtest_discover_tests(tests)

add_test(NAME tests_valgrind
    COMMAND valgrind --leak-check=full --error-exitcode=1 $<TARGET_FILE:tests>
)

include(CPack)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "test182 <test182@localhost>")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_NAME "calc_oop")

install(TARGETS calc_oop DESTINATION /usr/local/bin)


install(FILES config.json DESTINATION /etc/calc_oop)


install(FILES calculator.service DESTINATION /etc/systemd/system)