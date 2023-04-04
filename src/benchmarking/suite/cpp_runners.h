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

#pragma once
#include <vector>
#include <benchmark/benchmark.h>

struct degrees {
    int f(int n) {
        return 32 + n * (9.0 / 5.0);
    }

    int c(int n) {
        return (5.0 / 9.0) * (n - 32);
    }

    int work(int n) {
        return f(c(n));
    }

    void run(int n) {
        for(int m = 0; m < n; ++m) {
            benchmark::DoNotOptimize(work(m));
        }
    }
};

struct fact {
    int f(int n) {
        if(n <= 1) {
            return 1;
        } else {
            return n * f(n - 1);
        }
    }

    void run(int n) {
        for(int m = 0; m < n; ++m) {
            benchmark::DoNotOptimize(f(m));
        }
    }
};

struct fib {
    int f(int n) {
        if(n <= 1) {
            return n;
        } else {
            return f(n - 1) + f(n - 2);
        }
    }

    void run(int n) {
        for(int m = 0; m < n; ++m) {
            benchmark::DoNotOptimize(f(m));
        }
    }
};

struct iota {
    void run(int n) {
        std::vector<int> num;
        num.reserve(n);
        for(int m = 0; m < n; ++m) {
            num.emplace_back(m);
        }
        benchmark::DoNotOptimize(num);
    }
};