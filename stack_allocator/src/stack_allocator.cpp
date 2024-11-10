#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include "stack_allocator.h"

bool stack_allocator_t::create(uintptr_t size) {
    if ((create_flag_ == true) || (size < ALIGNMENT)) {
        return false;
    }

    memory_ = calloc(size, sizeof(char));
    if (memory_ == nullptr) {
        return false;
    }

    offset_ = (ALIGNMENT - (((uintptr_t) memory_) & ALIGNMENT_MASK)) & ALIGNMENT_MASK;
    memory_ = (void*) ((char*) memory_ + offset_);

    create_flag_ = true;
    size_ = size;
    used_ = memory_;
    return true;
}

void stack_allocator_t::destroy() {
    free(memory_);
    memory_ = nullptr;

    size_ = 0;
    offset_ = 0;
    used_ = nullptr;
    create_flag_ = false;
}

void* stack_allocator_t::allocate(uintptr_t size) {
    if ((size == 0) || (((char*) used_ + size + sizeof(header_t)) > (char*) memory_ + size_)) {
        return nullptr;
    }

    header_t* header = (header_t*) used_;
    header->size = size;
    used_ = (char*) used_ + sizeof(header_t);


    void* allocated_memory = used_;
    used_ = (char*) used_ + size;

    return allocated_memory;
}

void stack_allocator_t::deallocate(void* ptr) {
    if (ptr == nullptr) {
        return;
    }

    header_t* header = (header_t*) ((char*) ptr - sizeof(header_t));
    uintptr_t block_size = header->size;

    used_ = (char*) used_ - block_size - sizeof(header_t);
}

void stack_allocator_t::reset() {
    used_ = memory_;
}
