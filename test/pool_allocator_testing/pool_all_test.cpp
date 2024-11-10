#include <stdlib.h>
#include <stdio.h>
#include "logger.h"
#include "benchmark.h"
#include "pool_allocator.h"
#include <time.h>

void test_func_small_block_one(state_t state) {
    while (state) {
        pool_allocator_t allocator{};
        DoNotOptimize(allocator);
        int* a = nullptr;
        DoNotOptimize(a);
        allocator.create(8, 10000);
        for (size_t i = 0; i < 1000; i++) {
            allocator.allocate();
        }
        allocator.destroy();
        state = STOP;
    }
}

int main() {
    BENCHMARK(test_func_small_block_one);
    set_min_warmup_time(5);
    set_epsilon(0.05);
    run_benchmark();

    FILE* ostream = fopen("../test/reports/pool_test1.txt", "w");
    print_report(ostream);
    fclose(ostream);
}
