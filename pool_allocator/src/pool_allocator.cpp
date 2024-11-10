#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pool_allocator.h"

bool pool_allocator_t::create(size_t chunk_size, size_t size) {
    if (create_flag_ == true || size == 0 || chunk_size < sizeof(void*)) {
        return EXIT_FAILURE;
    }

    memory_ = calloc(size, chunk_size);
    if (memory_ == nullptr) {
        return EXIT_FAILURE;
    }

    size_ = size * chunk_size;
    chunk_size_ = chunk_size;
    head_chunk_ = memory_;

    void* next_block = (char*) memory_ + chunk_size_;
    for (size_t i = 0; i < size_ - chunk_size_; i += chunk_size_) {
        memcpy(((char*) memory_ + i), &next_block, sizeof(void*));
        next_block = (char*) next_block + chunk_size_;
    }

    next_block = nullptr;
    memcpy(((char*) memory_ + size_ - chunk_size_), &next_block, sizeof(void*));
    return EXIT_SUCCESS;
}

void pool_allocator_t::destroy() {
    free(memory_);
    memory_ = nullptr;

    size_ = 0;
    chunk_size_ = 0;
    head_chunk_ = nullptr;

}

void* pool_allocator_t::allocate() {
    if (head_chunk_ == nullptr) {
        return nullptr;
    }

    void* last_chunk = head_chunk_;
    memcpy(&head_chunk_, last_chunk, sizeof(void*));
    return last_chunk;
}

void pool_allocator_t::deallocate(void* chunk) {
    if (chunk == nullptr ) {
        return;
    }

    memcpy(chunk, head_chunk_, sizeof(void*));
    head_chunk_ = chunk;
}
