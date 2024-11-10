#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

class pool_allocator_t {
public:
    bool create(size_t chunk_size, size_t size);
    void destroy();
    void* allocate();
    void deallocate(void* chunk);
private:
    void* memory_{nullptr};
    bool create_flag_{false};
    size_t size_{0};

    void* head_chunk_{0};
    size_t chunk_size_{0};
};

#endif /* POOL_ALLOCATOR_H */
