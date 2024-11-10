#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "benchmark.h"
#include "linear_allocator.h"
#include <time.h>

void test_func1(state_t state) {
    while (state) {
        linear_allocator_t allocator = {};
        DoNotOptimize(allocator);
        allocator.create(1000000000);
        int* a = nullptr;
        DoNotOptimize(a);
        for (size_t i = 0; i < 1000; i++) {
            a = (int*) allocator.allocate(1);
        }
        allocator.destroy();
        state = STOP;
    }
}

void test_func2(state_t state) {
    while (state) {
        linear_allocator_t allocator = {};
        DoNotOptimize(allocator);
        allocator.create(1000000000);
        int* a = nullptr;
        DoNotOptimize(a);
        for (size_t i = 0; i < 1000; i++) {
            a = (int*) allocator.allocate(10);
        }
        allocator.destroy();
        state = STOP;
    }
}

void test_func3(state_t state) {
    while (state) {
        linear_allocator_t allocator = {};
        DoNotOptimize(allocator);
        allocator.create(1000000000);
        int* a = nullptr;
        DoNotOptimize(a);
        for (size_t i = 0; i < 1000; i++) {
            a = (int*) allocator.allocate(100);
        }
        allocator.destroy();
        state = STOP;
    }
}

void test_func4(state_t state) {
    while (state) {
        linear_allocator_t allocator = {};
        DoNotOptimize(allocator);
        allocator.create(1000000000);
        int* a = nullptr;
        DoNotOptimize(a);
        for (size_t i = 0; i < 1000; i++) {
            a = (int*) allocator.allocate(500);
        }
        allocator.destroy();
        state = STOP;
    }
}

void test_func5(state_t state) {
    while (state) {
        linear_allocator_t allocator = {};
        DoNotOptimize(allocator);
        allocator.create(1000000000);
        int* a = nullptr;
        DoNotOptimize(a);
        for (size_t i = 0; i < 1000; i++) {
            a = (int*) allocator.allocate(1000);
        }
        allocator.destroy();
        state = STOP;
    }
}

void test_func6(state_t state) {
    while (state) {
        linear_allocator_t allocator = {};
        DoNotOptimize(allocator);
        allocator.create(1000000000);
        int* a = nullptr;
        DoNotOptimize(a);
        for (size_t i = 0; i < 1000; i++) {
            a = (int*) allocator.allocate(10000);
        }
        allocator.destroy();
        state = STOP;
    }
}

void test_func7(state_t state) {
    while (state) {
        linear_allocator_t allocator = {};
        DoNotOptimize(allocator);
        allocator.create(1000000000);
        int* a = nullptr;
        DoNotOptimize(a);
        for (size_t i = 0; i < 1000; i++) {
            a = (int*) allocator.allocate(100000);
        }
        allocator.destroy();
        state = STOP;
    }
}

void test_func8(state_t state) {
    while (state) {
        linear_allocator_t allocator = {};
        DoNotOptimize(allocator);
        allocator.create(1000000000);
        int* a = nullptr;
        DoNotOptimize(a);
        for (size_t i = 0; i < 1000; i++) {
            a = (int*) allocator.allocate(800000); //200000 // 50000
        }
        allocator.destroy();
        state = STOP;
    }
}

void test_func9(state_t state) {
    while (state) {
        linear_allocator_t allocator = {};
        DoNotOptimize(allocator);
        allocator.create(10000000000);
        int* a = nullptr;
        DoNotOptimize(a);
        for (size_t i = 0; i < 1000; i++) {
            a = (int*) allocator.allocate(1000000); //500000 //1000000
        }
        allocator.destroy();
        state = STOP;
    }
}

int main() {
//     BENCHMARK(test_func1);
//     set_min_warmup_time(5);
//     set_epsilon(0.05);
//     run_benchmark();
//
//     FILE* ostream = fopen("../test/reports/linear_test1.txt", "w");
//     print_report(ostream);
//     fclose(ostream);
//
//     BENCHMARK(test_func2);
//     set_min_warmup_time(5);
//     set_epsilon(0.05);
//     run_benchmark();
//
//     ostream = fopen("../test/reports/linear_test2.txt", "w");
//     print_report(ostream);
//     fclose(ostream);
//
//     BENCHMARK(test_func3);
//     set_min_warmup_time(5);
//     set_epsilon(0.05);
//     run_benchmark();
//
//     ostream = fopen("../test/reports/linear_test3.txt", "w");
//     print_report(ostream);
//     fclose(ostream);
//
//     BENCHMARK(test_func4);
//     set_min_warmup_time(5);
//     set_epsilon(0.05);
//     run_benchmark();
//
//     ostream = fopen("../test/reports/linear_test4.txt", "w");
//     print_report(ostream);
//     fclose(ostream);
//
//
//     BENCHMARK(test_func5);
//     set_min_warmup_time(5);
//     set_epsilon(0.05);
//     run_benchmark();
//
//     ostream = fopen("../test/reports/linear_test5.txt", "w");
//     print_report(ostream);
//     fclose(ostream);
//
//
//     BENCHMARK(test_func6);
//     set_min_warmup_time(5);
//     set_epsilon(0.05);
//     run_benchmark();
//
//     ostream = fopen("../test/reports/linear_test6.txt", "w");
//     print_report(ostream);
//     fclose(ostream);
//
//     BENCHMARK(test_func7);
//     set_min_warmup_time(5);
//     set_epsilon(0.05);
//     run_benchmark();
//
//     ostream = fopen("../test/reports/linear_test7.txt", "w");
//     print_report(ostream);
//     fclose(ostream);

    BENCHMARK(test_func8);
    set_min_warmup_time(5);
    set_epsilon(0.05);
    run_benchmark();

    // FILE* ostream = fopen("../test/reports/linear_test12.txt", "w");
    // print_report(ostream);
    // fclose(ostream);

    BENCHMARK(test_func9);
    set_min_warmup_time(5);
    set_epsilon(0.05);
    run_benchmark();

    FILE* ostream = fopen("../test/reports/linear_test14.txt", "w");
    print_report(ostream);
    fclose(ostream);
}
