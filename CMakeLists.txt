cmake_minimum_required(VERSION 3.16)
project(Kepler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -O0")

include(FetchContent)

############ External dependencies ############
FetchContent_Declare(uni-algo
   GIT_REPOSITORY https://github.com/uni-algo/uni-algo.git
   GIT_SHALLOW ON  # Download the branch without its history
   GIT_TAG v0.6.0) # The version you want to download

FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1) # or a later release

FetchContent_Declare(Lyra
        GIT_REPOSITORY https://github.com/bfgroup/Lyra.git
        GIT_TAG        1.6.1) # or a later release

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.x)

FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG main)


FetchContent_MakeAvailable(uni-algo)
FetchContent_MakeAvailable(Catch2)
FetchContent_MakeAvailable(Lyra)
FetchContent_MakeAvailable(googletest googlebenchmark)

###############################################

file(GLOB_RECURSE Kepler_SRC CONFIGURE_DEPENDS
        "src/main.cpp"
        "src/cli.cpp"
        "src/core/*.h"
        "src/core/*.cpp"
        "src/interface/*.h"
        "src/interface/*.cpp"
        "src/testing/*.h"
        "src/testing/*.cpp")
add_executable(${PROJECT_NAME} ${Kepler_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE src)

file(GLOB_RECURSE KeplerBench_SRC CONFIGURE_DEPENDS
        "src/benchmarking/*.h"
        "src/benchmarking/*.cpp"
        "src/core/*.h"
        "src/core/*.cpp"
        "src/interface/*.h"
        "src/interface/*.cpp")
add_executable(KeplerBench ${KeplerBench_SRC})
target_include_directories(KeplerBench PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE uni-algo::uni-algo Catch2::Catch2 lyra benchmark::benchmark)
target_link_libraries(KeplerBench PRIVATE uni-algo::uni-algo Catch2::Catch2 lyra benchmark::benchmark)
