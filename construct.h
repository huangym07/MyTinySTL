#ifndef __CONSTRUCT_H__
#define __CONSTRUCT_H__

#include <new> // for placement new
#include "iterator.h"
#include "TypeTraits.h"

// 构造和析构对象
namespace MyTinySTL {
    template<typename T> 
    inline void construct(T* p) {
        new((void*) p) T();
    }
    template<typename T1, typename T2>
    inline void construct(T1* p, const T2& value) {
        new((void*) p) T1(value);
    }

    template<typename T>
    inline void destroy(T* p) {
        p->~T();
    }

    template<typename ForwardIt>
    inline void destroy(ForwardIt first, ForwardIt last) {
        destroy(first, last, value_type(first));
    }
    template<typename ForwardIt, typename T>
    inline void destroy(ForwardIt first, ForwardIt last, T* ptr) {
        typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
        destroy(first, last, trivial_destructor());
    }
    template<typename ForwardIt>
    inline void destroy(ForwardIt first, ForwardIt last, __true_type) {}
    template<typename ForwardIt>
    inline void destroy(ForwardIt first, ForwardIt last, __false_type) {
        for (; first != last; first++) {
            destroy(&(*first));
        }
    } 
}

#endif