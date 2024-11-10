#include <stdlib.h>
#include "linear_allocator.h"

bool linear_allocator_t::create(uintptr_t size) {
    if (create_flag_ || (size < ALIGNMENT)) {
        return EXIT_FAILURE;
    }

    memory_ = calloc(size, sizeof(char));
    if (memory_ == nullptr) {
        return EXIT_FAILURE;
    }

    offset_ = (ALIGNMENT - (((uintptr_t) memory_) & ALIGNMENT_MASK)) & ALIGNMENT_MASK;
    memory_ = (void*) ((char*) memory_ + offset_);

    create_flag_ = true;
    size_ = size;
    return EXIT_SUCCESS;
}

void linear_allocator_t::destroy() {
    free(memory_);
    memory_ = nullptr;

    size_ = 0;
    offset_ = 0;
    create_flag_ = false;
}

void* linear_allocator_t::allocate(uintptr_t size) {
    if (size == 0 || offset_ + size > size_) {
        return nullptr;
    }

    offset_ += (ALIGNMENT - (((uintptr_t) memory_ + offset_) & ALIGNMENT_MASK)) & ALIGNMENT_MASK;
    offset_ += size;
    return (char*) memory_ + offset_;
}
