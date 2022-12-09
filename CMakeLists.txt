cmake_minimum_required(VERSION 3.23)
project(Kepler)

set(CMAKE_CXX_STANDARD 20)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.78.0 REQUIRED COMPONENTS)

include(FetchContent)

FetchContent_Declare(uni-algo
        URL https://github.com/uni-algo/uni-algo/archive/refs/tags/v0.6.0.tar.gz)

file(GLOB Kepler_SRC CONFIGURE_DEPENDS
        "src/main.cpp"
        "src/core/*.h"
        "src/core/*.cpp"
        "src/core/lexer/*.h"
        "src/core/lexer/*.cpp"
        "src/core/env/*.h"
        "src/core/env/*.cpp"
)

add_executable(${PROJECT_NAME} ${Kepler_SRC})

FetchContent_MakeAvailable(uni-algo)
target_link_libraries(${PROJECT_NAME} PRIVATE uni-algo::uni-algo Boost::boost)