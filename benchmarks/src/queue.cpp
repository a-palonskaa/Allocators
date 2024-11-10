// #include <assert.h>
// #include <stdlib.h>
// #include <string.h>
//
// #include "queue.h"
//
// error_t cb_ctor(circ_buffer_t* circ_buffer, size_t capacity, size_t elm_width) {
//     if (!capacity) {
//         return NULL_CAPACITY_ERROR;
//     }
//
//     vec_err_t err = circ_buffer->buffer_holder.ctor(elm_width);
//     if (err != OK) {
//         return MEM_ALLOCATION_ERROR;
//     }
//
//     err = circ_buffer->buffer_holder.reserve(capacity);
//     if (err != OK) {
//         circ_buffer->buffer_holder.dtor();
//         return MEM_ALLOCATION_ERROR;
//     }
//
//     circ_buffer->head = circ_buffer->buffer_holder.head_ptr();
//     circ_buffer->tail = circ_buffer->buffer_holder.tail_ptr();
//
//     return NO_ERRORS;
// }
//
// void cb_dtor(circ_buffer_t* circ_buffer) {
//     assert(circ_buffer);
//
//     circ_buffer->buffer_holder.dtor();
//
//     circ_buffer->tail = nullptr;
//     circ_buffer->head = nullptr;
// }
//
// void cb_push(circ_buffer_t* circ_buffer, void* elm) {
//     assert(circ_buffer);
//     assert(elm);
//     printf(" %f ", *((double*) elm));
//     vec_err_t err = circ_buffer->buffer_holder.push_back(elm);
//     if (err != OK) {
//         return;
//     }
//
//     circ_buffer->head = circ_buffer->buffer_holder.head_ptr();
//
//     if ((size_t)circ_buffer->head == (size_t)circ_buffer->buffer_holder.tail_ptr() +
//             circ_buffer->buffer_holder.get_capacity() * circ_buffer->buffer_holder.get_elem_width()) {
//         circ_buffer->head = circ_buffer->buffer_holder.tail_ptr();
//     }
// }
//
// void cb_pop(circ_buffer_t* circ_buffer, void* elm) {
//     assert(circ_buffer);
//     assert(elm);
//
//     memcpy(elm, circ_buffer->tail, circ_buffer->buffer_holder.get_elem_width());
//
//     circ_buffer->tail = (char*)circ_buffer->tail + circ_buffer->buffer_holder.get_elem_width();
//
//     if ((size_t)circ_buffer->tail == (size_t)circ_buffer->buffer_holder.tail_ptr() +
//             circ_buffer->buffer_holder.get_capacity() * circ_buffer->buffer_holder.get_elem_width()) {
//         circ_buffer->tail = circ_buffer->buffer_holder.tail_ptr();
//     }
// }

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

error_t cb_ctor(circ_buffer_t* circ_buffer, size_t capacity, size_t elm_width) {
    if (capacity == 0) {
        return NULL_CAPACITY_ERROR;
    }

    circ_buffer->buffer = calloc(capacity, elm_width);
    if (circ_buffer->buffer == nullptr) {
        return MEM_ALLOCATION_ERROR;
    }

    circ_buffer->elm_width = elm_width;
    circ_buffer->capacity = capacity;
    circ_buffer->size = 0;

    circ_buffer->head = circ_buffer->buffer;
    circ_buffer->tail = circ_buffer->buffer;
    return NO_ERRORS;
}

void cb_dtor(circ_buffer_t* circ_buffer) {
    assert(circ_buffer);
    free(circ_buffer->buffer);
    circ_buffer->buffer = nullptr;

    circ_buffer->size = 0;
    circ_buffer->capacity = 0;

    circ_buffer->head = nullptr;
    circ_buffer->tail = nullptr;
}

void cb_push(circ_buffer_t* circ_buffer, void* elm) {
    assert(circ_buffer);
    assert(elm);

    if (circ_buffer->size == circ_buffer->capacity) {
        circ_buffer->tail = (char*)circ_buffer->tail + circ_buffer->elm_width;
        if ((char*)circ_buffer->tail == (char*)circ_buffer->buffer + circ_buffer->capacity * circ_buffer->elm_width) {
            circ_buffer->tail = circ_buffer->buffer;
        }
    } else {
        circ_buffer->size++;
    }

    memcpy(circ_buffer->head, elm, circ_buffer->elm_width);

    circ_buffer->head = (char*)circ_buffer->head + circ_buffer->elm_width;
    if ((char*)circ_buffer->head == (char*)circ_buffer->buffer + circ_buffer->capacity * circ_buffer->elm_width) {
        circ_buffer->head = circ_buffer->buffer;
    }
}

void cb_pop(circ_buffer_t* circ_buffer, void* elm) {
    assert(circ_buffer);
    assert(elm);

    if (circ_buffer->size == 0) {
        return;
    }

    memcpy(elm, circ_buffer->tail, circ_buffer->elm_width);

    circ_buffer->tail = (char*)circ_buffer->tail + circ_buffer->elm_width;
    if ((char*)circ_buffer->tail == (char*)circ_buffer->buffer + circ_buffer->capacity * circ_buffer->elm_width) {
        circ_buffer->tail = circ_buffer->buffer;
    }

    circ_buffer->size--;
}

int cb_is_empty(circ_buffer_t* circ_buffer) {
    return circ_buffer->size == 0;
}

int cb_is_full(circ_buffer_t* circ_buffer) {
    return circ_buffer->size == circ_buffer->capacity;
}
