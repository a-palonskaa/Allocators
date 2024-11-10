#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>

typedef enum {
	OK                  = 0,
	EMPTY_VECTOR        = 2, //FIXME - mem allocation err
	MEM_ALLOCATON_ERROR = 3,
} vec_err_t;

class vector_t {
public:
	vector_t() = default;
    ~vector_t() = default;

	vec_err_t ctor(size_t elmwidth);
	void dtor();

	vec_err_t memory_add_to_fit(size_t len);
	vec_err_t memory_add(size_t new_capacity);
	vec_err_t reserve(size_t new_capacity) ;
	vec_err_t shrink_to_fit();

	vec_err_t push_back(void* src);
	vec_err_t pop_back(void* dst);

	void at(void* dst, size_t index);

	void insert(size_t pos, void* elm);
	void erase_elm(size_t pos);
	void erase_range( size_t first, size_t last);
	void clear();

	void* element_ptr(size_t n);
	size_t get_size();
	size_t get_elem_width();
	void* head_ptr();
	void* tail_ptr();
	bool is_empty();
	size_t get_capacity();
private:
	bool has_space(size_t len);
	void* data;
	size_t size;
	size_t capacity;
	size_t elm_width;
};

#endif /* VECTOR_H */
