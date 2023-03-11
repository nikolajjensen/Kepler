cmake_minimum_required(VERSION 3.16)
project(Kepler)

set(CMAKE_CXX_STANDARD 20)

#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
set(CMAKE_CXX_FLAGS "-O3")
#find_package(Boost 1.74.0 REQUIRED COMPONENTS)

include(FetchContent)

 FetchContent_Declare(uni-algo
   GIT_REPOSITORY https://github.com/uni-algo/uni-algo.git
   GIT_SHALLOW ON  # Download the branch without its history
   GIT_TAG v0.6.0) # The version you want to download

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)

FetchContent_Declare(
        Lyra
        GIT_REPOSITORY https://github.com/bfgroup/Lyra.git
        GIT_TAG        1.6.1 # or a later release
)

file(GLOB_RECURSE Kepler_SRC CONFIGURE_DEPENDS
        "src/*.h"
        "src/*.cpp"
        "src/*.tpp"
)

add_executable(${PROJECT_NAME} ${Kepler_SRC})

FetchContent_MakeAvailable(uni-algo)
FetchContent_MakeAvailable(Catch2)
FetchContent_MakeAvailable(Lyra)
#target_link_libraries(${PROJECT_NAME} PRIVATE uni-algo::uni-algo Boost::boost Catch2::Catch2 lyra)
target_link_libraries(${PROJECT_NAME} PRIVATE uni-algo::uni-algo Catch2::Catch2 lyra)
target_include_directories(${PROJECT_NAME} PRIVATE src)