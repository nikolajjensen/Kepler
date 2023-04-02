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

#include "kepler_fixture.h"

BENCHMARK_DEFINE_F(KeplerFixture, Degrees)(benchmark::State& state) {
    std::string suffix = std::to_string(state.range(0));
    load_file("../benchmarking/files/degrees/degrees" + suffix + ".kpl");

    for(auto _ : state) {
        execute();
    }
}

BENCHMARK_DEFINE_F(KeplerFixture, Fact)(benchmark::State& state) {
    std::string suffix = std::to_string(state.range(0));
    load_file("../benchmarking/files/fact/fact" + suffix + ".kpl");

    for(auto _ : state) {
        execute();
    }
}

BENCHMARK_DEFINE_F(KeplerFixture, Fib)(benchmark::State& state) {
    std::string suffix = std::to_string(state.range(0));
    load_file("../benchmarking/files/fib/fib" + suffix + ".kpl");

    for(auto _ : state) {
        execute();
    }
}

BENCHMARK_DEFINE_F(KeplerFixture, Iota)(benchmark::State& state) {
    std::string suffix = std::to_string(state.range(0));
    load_file("../benchmarking/files/iota/iota" + suffix + ".kpl");

    for(auto _ : state) {
        execute();
    }
}

BENCHMARK_DEFINE_F(KeplerFixture, Life)(benchmark::State& state) {
    std::string suffix = std::to_string(state.range(0));
    load_file("../benchmarking/files/life/life" + suffix + ".kpl");

    for(auto _ : state) {
        execute();
    }
}

BENCHMARK_DEFINE_F(KeplerFixture, Mandelbrot)(benchmark::State& state) {
    std::string suffix = std::to_string(state.range(0));
    load_file("../benchmarking/files/mandelbrot/mandelbrot" + suffix + ".kpl");

    for(auto _ : state) {
        execute();
    }
}

BENCHMARK_REGISTER_F(KeplerFixture, Degrees)->RangeMultiplier(10)->Range(1, 100000)->Repetitions(30);
BENCHMARK_REGISTER_F(KeplerFixture, Fact)->RangeMultiplier(10)->Range(1, 10000)->Repetitions(30);
BENCHMARK_REGISTER_F(KeplerFixture, Fib)->RangeMultiplier(10)->Range(1, 10000)->Repetitions(30);
BENCHMARK_REGISTER_F(KeplerFixture, Iota)->RangeMultiplier(10)->Range(100000, 100000000)->Repetitions(30);
BENCHMARK_REGISTER_F(KeplerFixture, Life)->RangeMultiplier(10)->Range(10, 1000)->Repetitions(30);
BENCHMARK_REGISTER_F(KeplerFixture, Mandelbrot)->RangeMultiplier(10)->Range(10, 1000)->Repetitions(30);

BENCHMARK_MAIN();
