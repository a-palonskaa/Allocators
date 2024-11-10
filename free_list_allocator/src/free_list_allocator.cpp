#include <stdlib.h>
#include <stdio.h>
#include "free_list_allocator.h"

bool free_list_allocator_t::create(uintptr_t size) {
    if (create_flag_ || (size < ALIGNMENT)) {
        return EXIT_FAILURE;
    }

    memory_ = calloc(size, sizeof(char));
    if (memory_ == nullptr) {
        return EXIT_FAILURE;
    }

    header_t* first_block = (header_t*)memory_;
    first_block->size = size - sizeof(header_t);
    first_block->next = nullptr;
    first_block->prev = nullptr;

    free_chunk_ = first_block;
    size_ = size;
    create_flag_ = true;
    return EXIT_SUCCESS;
}

void free_list_allocator_t::destroy() {
    free(memory_);
    memory_ = nullptr;
    size_ = 0;
    free_chunk_ = nullptr;
    create_flag_ = false;
}

void* free_list_allocator_t::allocate(uintptr_t size) {
    if (size == 0 || free_chunk_ == nullptr) {
        return nullptr;
    }

    header_t* block = (header_t*)free_chunk_;

    while (block != nullptr) {
        if (block->size >= size) {
            if (block->size > size + sizeof(header_t)) {
                header_t* new_block = (header_t*)((char*)block + size + sizeof(header_t));
                new_block->size = block->size - size - sizeof(header_t);
                new_block->next = block->next;
                new_block->prev = block;

                block->size = size;
                block->next = new_block;

                if (new_block->next != nullptr) {
                    ((header_t*)new_block->next)->prev = new_block;
                }
            }

            if (block->prev != nullptr) {
                ((header_t*)block->prev)->next = block->next;
            } else {
                free_chunk_ = block->next;
            }

            if (block->next != nullptr) {
                ((header_t*)block->next)->prev = block->prev;
            }

            return (void*)((char*)block + sizeof(header_t));
        }

        block = (header_t*) block->next;
    }
    return nullptr;
}

void free_list_allocator_t::deallocate(void* ptr) {
    if (ptr == nullptr) {
        return;
    }

    header_t* block = (header_t*)((char*)ptr - sizeof(header_t));

    block->next = free_chunk_;
    block->prev = nullptr;

    if (free_chunk_ != nullptr) {
        ((header_t*)free_chunk_)->prev = block;
    }

    free_chunk_ = block;
}
