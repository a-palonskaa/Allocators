#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "benchmark.h"
#include <time.h>

void test_func_small_block_one(state_t state) {
    while (state) {
        int* am = nullptr;
        DoNotOptimize(am);
        srand(time(NULL));
        int random_number = 0;
        DoNotOptimize(random_number);
        for (size_t i = 0; i < 1000; i++) {
            am = (int*) calloc(1000000000, 1);
            free(am);
        }
        state = STOP;
    }
}

int main() {
    BENCHMARK(test_func_small_block_one);
    set_min_warmup_time(5);
    set_epsilon(0.05);
    run_benchmark();

    FILE* ostream = fopen("../test/reports/calloc_test1.txt", "w");
    print_report(ostream);
    fclose(ostream);
}
