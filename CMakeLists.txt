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

# --- Fetch FTXUI --------------------------------------------------------------
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        # Important: Specify a GIT_TAG XXXXX here.
        )

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# ------------------------------------------------------------------------------

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


file(GLOB Kepler_SRC CONFIGURE_DEPENDS
        "src/main.cpp"
        "src/core/*.h"
        "src/core/*.cpp"
        "src/core/exceptions/*.h"
        "src/core/exceptions/*.cpp"
        "src/core/lexer/*.h"
        "src/core/lexer/*.cpp"
        "src/core/parser/*.h"
        "src/core/parser/*.cpp"
        "src/core/interpreter/*.h"
        "src/core/interpreter/*.cpp"
        "src/core/interpreter/*.tpp"
        "src/core/env/*.h"
        "src/core/env/*.cpp"
        "src/tui/*.h"
        "src/tui/*.cpp"
        "src/testing/*.h"
        "src/testing/*.cpp"
)

add_executable(${PROJECT_NAME} ${Kepler_SRC})

FetchContent_MakeAvailable(uni-algo)
FetchContent_MakeAvailable(Catch2)
FetchContent_MakeAvailable(Lyra)
target_link_libraries(${PROJECT_NAME} PRIVATE uni-algo::uni-algo Boost::boost Catch2::Catch2 lyra)
target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME}
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component # Not needed for this example.
        )