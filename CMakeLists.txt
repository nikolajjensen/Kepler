cmake_minimum_required(VERSION 3.23)
project(Kepler)

set(CMAKE_CXX_STANDARD 20)

file(GLOB Kepler_SRC CONFIGURE_DEPENDS
        "src/main.cpp"
        "src/core/*.h"
        "src/core/*.cpp"
)

add_executable(Kepler ${Kepler_SRC})
