#ifndef FREE_LIST_ALLOCATOR_H
#define FREE_LIST_ALLOCATOR_H

#include <stdio.h>

//#ifdef __ALIGNMENT__
    #if defined(_MSC_VER)
        #define ALIGNMENT 8
    #elif defined(__GNUC__)
        #if defined(__x86_64__) || defined(__aarch64__) || defined(_WIN64)
            #define ALIGNMENT 8
        #elif defined(__i386__) || defined(__arm__) || defined(_WIN32)
            #define ALIGNMENT 4
        #else
            #define ALIGNMENT 2 // NOTE: or 1
        #endif /* 64-bits / 32-bits / other */
    #elif defined(__arm__)
        #define ALIGNMENT 8
    #elif defined(__powerpc__)
        #define ALIGNMENT 8
    #else
        #define ALIGNMENT 4
    #endif /* compilator type */
//#endif /* __ALIGNMENT__ */

#define ALIGNMENT_MASK ((ALIGNMENT) - 1)

typedef struct {
    size_t size;
    void* next;
    void* prev;
} header_t;

class free_list_allocator_t {
public:
    bool create(size_t size);
    void destroy();
    void* allocate(size_t size);
    void deallocate(void* ptr);
private:
    void* memory_{nullptr};
    size_t size_{0};
    bool create_flag_{false};
    void* free_chunk_{nullptr};
};

#endif /* LINEAR_ALLOCATOR_H */
