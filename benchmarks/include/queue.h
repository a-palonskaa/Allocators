#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdio.h>
// #include "vector.h"
//
// typedef struct {
//     vector_t buffer_holder;
//     //size_t size;
//
//     void* head;
//     void* tail;
// } circ_buffer_t;
//
// typedef enum {
//     NO_ERRORS               = 1 << 0, // 0x0000
//     NULL_ELM_WIDTH_ERROR    = 1 << 1, // 0x0001
//     NULL_CAPACITY_ERROR     = 1 << 2, // 0x0002
//     MEM_ALLOCATION_ERROR    = 1 << 3, // 0x0004
//     FULL_BUFFER             = 1 << 4, // 0x0008
// } error_t;
//
// error_t cb_ctor(circ_buffer_t* circ_buffer, size_t capacity, size_t elm_width);
// void cb_dtor(circ_buffer_t* circ_buffer);
//
// void cb_push(circ_buffer_t* circ_buffer, void* elm);
// void cb_pop(circ_buffer_t* circ_buffer, void* elm);

typedef enum {
    NO_ERRORS,
    NULL_CAPACITY_ERROR,
    MEM_ALLOCATION_ERROR
} error_t;

typedef struct {
    void* buffer;
    size_t capacity;
    size_t size;
    size_t elm_width;

    void* head;
    void* tail;
} circ_buffer_t;

error_t cb_ctor(circ_buffer_t* circ_buffer, size_t capacity, size_t elm_width);
void cb_dtor(circ_buffer_t* circ_buffer);

void cb_push(circ_buffer_t* circ_buffer, void* elm);
void cb_pop(circ_buffer_t* circ_buffer, void* elm);

int cb_is_empty(circ_buffer_t* circ_buffer);
int cb_is_full(circ_buffer_t* circ_buffer);

#endif /* CIRCULAR_BUFFER_H */
