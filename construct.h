#ifndef __CONSTRUCT_H__
#define __CONSTRUCT_H__

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
}

#endif