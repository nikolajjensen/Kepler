//
// Copyright 2023 Nikolaj Banke Jensen.
//
// This file is part of Kepler.
// 
// Kepler is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Kepler is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License 
// along with Kepler. If not, see <https://www.gnu.org/licenses/>.
//
#include <benchmark/benchmark.h>
#include "suite/kepler_fixture.h"
#include "suite/cpp_runners.h"

///////////////////////////////////////////////////////////////////
//// C++ Benchmarks
///////////////////////////////////////////////////////////////////

/******************************************************************
 * C++ Degrees
 ******************************************************************/
static void CppDegrees(benchmark::State& state) {
    int n = state.range(0);
    degrees f;

    for(auto _ : state) {
        f.run(n);
    }
}

/******************************************************************
 * C++ Fact
 ******************************************************************/
static void CppFact(benchmark::State& state) {
    int n = state.range(0);
    fact f;

    for(auto _ : state) {
        f.run(n);
    }
}

/******************************************************************
 * C++ Fib
 ******************************************************************/
static void CppFib(benchmark::State& state) {
    int n = state.range(0);
    fib f;

    for(auto _ : state) {
        f.run(n);
    }
}

/******************************************************************
 * C++ Iota
 ******************************************************************/
static void CppIota(benchmark::State& state) {
    int n = state.range(0);
    iota f;

    for(auto _ : state) {
        f.run(n);
    }
}

///////////////////////////////////////////////////////////////////

/******************************************************************
 * Kepler Degrees
 ******************************************************************/
BENCHMARK_DEFINE_F(KeplerFixture, KeplerDegrees)(benchmark::State& state) {
    std::string suffix = std::to_string(state.range(0));
    load_file("../benchmarking/files/degrees/degrees" + suffix + ".kpl");

    for(auto _ : state) {
        execute();
    }
}

/******************************************************************
 * Kepler Fact
 ******************************************************************/
BENCHMARK_DEFINE_F(KeplerFixture, KeplerFact)(benchmark::State& state) {
    std::string suffix = std::to_string(state.range(0));
    load_file("../benchmarking/files/fact/fact" + suffix + ".kpl");

    for(auto _ : state) {
        execute();
    }
}

/******************************************************************
 * Kepler Fib
 ******************************************************************/
BENCHMARK_DEFINE_F(KeplerFixture, KeplerFib)(benchmark::State& state) {
    std::string suffix = std::to_string(state.range(0));
    load_file("../benchmarking/files/fib/fib" + suffix + ".kpl");

    for(auto _ : state) {
        execute();
    }
}

/******************************************************************
 * Kepler Iota
 ******************************************************************/
BENCHMARK_DEFINE_F(KeplerFixture, KeplerIota)(benchmark::State& state) {
    std::string suffix = std::to_string(state.range(0));
    load_file("../benchmarking/files/iota/iota" + suffix + ".kpl");

    for(auto _ : state) {
        execute();
    }
}

/******************************************************************
 * Kepler Life
 ******************************************************************/
BENCHMARK_DEFINE_F(KeplerFixture, KeplerLife)(benchmark::State& state) {
    std::string suffix = std::to_string(state.range(0));
    load_file("../benchmarking/files/life/life" + suffix + ".kpl");

    for(auto _ : state) {
        execute();
    }
}

/******************************************************************
 * Kepler Mandelbrot
 ******************************************************************/
BENCHMARK_DEFINE_F(KeplerFixture, KeplerMandelbrot)(benchmark::State& state) {
    std::string suffix = std::to_string(state.range(0));
    load_file("../benchmarking/files/mandelbrot/mandelbrot" + suffix + ".kpl");

    for(auto _ : state) {
        execute();
    }
}

/******************************************************************
 * C++ Benchmarks
 ******************************************************************/
BENCHMARK(CppDegrees)->RangeMultiplier(10)->Range(1, 100000)->Repetitions(30);
BENCHMARK(CppFact)->RangeMultiplier(2)->Range(1, 32)->Repetitions(30);
BENCHMARK(CppFib)->RangeMultiplier(2)->Range(1, 32)->Repetitions(30);
BENCHMARK(CppIota)->RangeMultiplier(10)->Range(10, 1000000)->Repetitions(30);

/******************************************************************
 * Kepler Benchmarks
 ******************************************************************/
BENCHMARK_REGISTER_F(KeplerFixture, KeplerDegrees)->RangeMultiplier(10)->Range(1, 100000)->Repetitions(30);
BENCHMARK_REGISTER_F(KeplerFixture, KeplerFact)->RangeMultiplier(2)->Range(1, 32)->Repetitions(30);
BENCHMARK_REGISTER_F(KeplerFixture, KeplerFib)->RangeMultiplier(2)->Range(1, 32)->Repetitions(30);
BENCHMARK_REGISTER_F(KeplerFixture, KeplerIota)->RangeMultiplier(10)->Range(10, 1000000)->Repetitions(30);
BENCHMARK_REGISTER_F(KeplerFixture, KeplerLife)->Arg(5)->Arg(10)->Arg(100)->Repetitions(30);
BENCHMARK_REGISTER_F(KeplerFixture, KeplerMandelbrot)->Arg(10)->Arg(100)->Arg(500)->Repetitions(30);

BENCHMARK_MAIN();
