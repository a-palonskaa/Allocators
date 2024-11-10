#ifndef STACK_ALLOCATOR_H
#define STACK_ALLOCATOR_H

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

class stack_allocator_t {
public:
    bool create(uintptr_t size);
    void destroy();
    void* allocate(uintptr_t size);
    void deallocate(void* ptr);
    void reset();
private:
    typedef struct {
        uintptr_t size;
    } header_t;

    void* memory_{nullptr};
    bool create_flag_{false};
    void* used_{nullptr};

    uintptr_t size_{0};
    uintptr_t offset_{0};
};

#endif /* STACK_ALLOCATOR_H */
