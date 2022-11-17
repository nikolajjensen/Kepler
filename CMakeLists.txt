cmake_minimum_required(VERSION 3.23)
project(Kepler)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(uni-algo
        URL https://github.com/uni-algo/uni-algo/archive/refs/tags/v0.6.0.tar.gz)
FetchContent_Declare(re2
        URL https://github.com/google/re2/archive/refs/tags/2022-06-01.tar.gz)

file(GLOB Kepler_SRC CONFIGURE_DEPENDS
        "src/main.cpp"
        "src/core/*.h"
        "src/core/*.cpp"
)

add_executable(Kepler ${Kepler_SRC})

FetchContent_MakeAvailable(uni-algo)
FetchContent_MakeAvailable(re2)
target_link_libraries(${PROJECT_NAME} PRIVATE uni-algo::uni-algo)
target_link_libraries(${PROJECT_NAME} PRIVATE re2::re2)