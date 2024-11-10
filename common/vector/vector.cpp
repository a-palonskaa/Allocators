#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include "vector.h"
#include "logger.h"

//============================================================================================

vec_err_t vector_t::ctor(size_t elmwidth) {
	assert(elmwidth >= 1);

	data = calloc(elm_width, sizeof(char));
	if (data == nullptr) {
		LOG(ERROR, "Memory allocation error\n" STRERROR(errno));
		return MEM_ALLOCATON_ERROR;
	}

	elm_width = elmwidth;
	capacity = 1;
	size = 0;
	return OK;
}

void vector_t::dtor() {
	free(data);
	data = nullptr;

	size = 0;
	capacity = 0;
	elm_width = 0;
}
//============================================================================================

vec_err_t vector_t::push_back(void* src) {
	assert(src != nullptr);

	vec_err_t memory_add_status = memory_add_to_fit(size + 1);
	if (memory_add_status != OK) {
		return memory_add_status;
	}

	memcpy((char*) data + size, src,  elm_width);
	size += elm_width;
	return OK;
}

vec_err_t vector_t::pop_back(void* dst) {
	assert(dst != nullptr);

	if (size < elm_width) {
		return EMPTY_VECTOR;
	}

	memcpy(dst, (char*) data + size - elm_width, elm_width);
	memset((char*) data + size - elm_width, 0, elm_width);
	size -=  elm_width;
	return OK;
}

//============================================================================================

bool vector_t::has_space(size_t len) {
	return capacity >= (size + len);
}

vec_err_t vector_t::memory_add_to_fit(size_t len) {
	if (has_space(len)) {
		return OK;
	}

	do {
		capacity *= 2;
	} while (!has_space(len));

	void* new_data = realloc(data, capacity * elm_width);
	if (new_data == nullptr) {
		LOG(ERROR, "Memory allocation error\n" STRERROR(errno));
		return EMPTY_VECTOR;
	}

	data = new_data;
	return OK;
}

vec_err_t vector_t::memory_add(size_t new_capacity) {
	assert(new_capacity != 0);

	void* new_data = realloc(data, new_capacity * elm_width);
	if (new_data == nullptr) {
		LOG(ERROR, "Memory allocation error\n" STRERROR(errno));
		return MEM_ALLOCATON_ERROR;
	}

	capacity = new_capacity;
	data = new_data;
	return OK;
}

vec_err_t vector_t::reserve(size_t new_capacity) {
	if (capacity >= new_capacity) {
		return OK;
	}
    return memory_add(new_capacity);
}

vec_err_t vector_t::shrink_to_fit() {
	return memory_add(size);
}

//============================================================================================

void vector_t::insert(size_t pos, void* elm) {
	assert(elm != nullptr);

	memcpy((char*) data + (pos - 1) * elm_width, elm, (size - pos) * elm_width);
}

void vector_t::erase_elm(size_t pos) {
    memcpy((char*) data + (pos - 1) * elm_width, data, (size-- - pos) * elm_width);
	memset((char*) data + size * elm_width, 0, elm_width);
}

void vector_t::erase_range(size_t first, size_t last) {
	if (last == first) {
		return;
	}
	else if (last < first) {
		size_t new_last = first;
		first = last;
		last = new_last;
	}

	memcpy((char*) data + (first - 1) *  elm_width, (char*) data + last *  elm_width,
		    (size - last) *  elm_width);
	size -= 1 + last - first;

	memset((char*) data + size * elm_width, 0,  elm_width * (1 + last - first));
}

void vector_t::clear() {
	memset(data, 0, size * elm_width);
	size = 0;
}

void vector_t::at(void* dst, size_t index) {
	assert(dst != nullptr);

	if (index > size) {
		return;
	}

	memcpy(dst, data, elm_width);
}

//============================================================================================

void* vector_t::element_ptr(size_t n) {
	if (n > size) {
		return nullptr;
	}
	return (char*) data + (elm_width * n);
}

size_t vector_t::get_size() {
	return size;
}

size_t vector_t::get_elem_width() {
	return elm_width;
}

size_t vector_t::get_capacity() {
	return capacity;
}

bool vector_t::is_empty() {
	return !size;
}

void* vector_t::tail_ptr() {
	return data;
}

void* vector_t::head_ptr() {
	return (void*)((size_t) data + size * elm_width);
}
