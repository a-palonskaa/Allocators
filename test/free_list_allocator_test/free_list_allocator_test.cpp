#include <stdlib.h>
#include <stdio.h>
#include "logger.h"
#include "benchmark.h"
#include "free_list_allocator.h"
#include <time.h>

void test_func_small_block_one(state_t state) {
    while (state) {
        free_list_allocator_t allocator{};
        DoNotOptimize(allocator);
        allocator.create(2000000000);
        srand(time(NULL));
        int random_number = 0;
        DoNotOptimize(random_number);
        int* a = nullptr;
        DoNotOptimize(a);
        for (size_t i = 0; i < 1000; i++) {
            a = (int*) allocator.allocate(1000000000);
            allocator.deallocate(a);
        }
        allocator.destroy();
        state = STOP;
    }
}

int main() {
    BENCHMARK(test_func_small_block_one);
    set_min_warmup_time(1);
    set_epsilon(0.05);
    run_benchmark();

    FILE* ostream = fopen("../test/reports/list_test1.txt", "w");
    print_report(ostream);
    fclose(ostream);
}
