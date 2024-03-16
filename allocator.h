#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#include "alloc.h"
#include "construct.h"

namespace MyTinySTL {
    // 用 allocator 包装 alloc 和 construct、destroy   
    template<typename T>
    class allocator {
    private:
        typedef T			value_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
    public:
        static void* allocate();
        static void* allocate(size_t n);
        static void deallocate(T* ptr);
        static void deallocate(T* ptr, size_t n);

        static void construct(T* ptr);
        static void construct(T* ptr, const T& value);
        static void destroy(T* ptr);
        static void destroy(T* first, T* last);
    };
}

#endif