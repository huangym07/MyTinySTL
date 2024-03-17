#ifndef __UNINITIALIZED_H__
#define __UNINITIALIZED_H__

#include <memory> // for std::copy
#include "iterator.h"
#include "TypeTraits.h"
#include "construct.h"

// 添加对内存操作的全局工具函数 copy fill fill_n
namespace MyTinySTL {

    /********************************** uninitialized_copy ***********************************/
    template<class InputIt, class ForwardIt>
    inline ForwardIt
        uninitialized_cpoy(InputIt first, InputIt last, ForwardIt result) {
            return uninitialized_cpoy(first, last, result, value_type(result));
    }

    template<class InputIt, class ForwardIt, class T>
    inline ForwardIt
        uninitialized_cpoy(InputIt first, InputIt last, ForwardIt result, T* ptr) {
            typedef typename __type_traits<T>::is_POD_tyope is_POD_type;
            return uninitialized_cpoy_aux(first, last, result, is_POD_type());
    }
    template<class InputIt, class ForwardIt>
    inline ForwardIt
        uninitialized_cpoy_aux(InputIt first, InputIt last, ForwardIt result, __true_type) {
            return std::copy(first, last, result);
    }
    template<class InputIt, class ForwardIt>
    inline ForwardIt
        uninitialized_cpoy_aux(InputIt first, InputIt last, ForwardIt result, __false_type) {
            for (; first != last; ++first, ++result) {
                construct(&(*result), *first);
            }
            return result;
    }
    

    /********************************** uninitialized_fill ***********************************/
    template<class InputIt, class T>
    inline void
        uninitialized_fill_aux(InputIt first, InputIt last, const T& x, __true_type) {
            std::fill(first, last, x);
    }
    template<class InputIt, class T>
    inline void 
        uninitialized_fill_aux(InputIt first, InputIt last, const T& x, __false_type) {
            for (; first != last; ++first) {
                construct(&(*first), x);
            }
    }
    template<class InputIt, class T1, class T2>
    inline void
        uninitialized_fill(InputIt first, InputIt last, const T1& x, T2* ptr) {
            typedef typename __type_traits<T2>::is_POD_type is_POD_type;
            uninitialized_fill_aux(first, last, x, is_POD_type());
    }
    template<class InputIt, class T>
    inline void
        uninitialized_fill(InputIt first, InputIt last, const T& x) {
            uninitialized_fill(first, last, x, value_type(first));
    }
    
    


    /********************************** uninitialized_fill_n ***********************************/
    template<class ForwardIt, class Size, class T>
    inline void
        uninitialized_fill_n_aux(ForwardIt first, Size n, const T& x, __true_type) {
            std::fill_n(first, n, x);
    }
    template<class ForwardIt, class Size, class T>
    inline void
        uninitialized_fill_n_aux(ForwardIt first, Size n, const T& x, __false_type) {
            for (; n--; ++first) {
                construct(&*first, x);
            }
    }
    template<class ForwardIt, class Size, class T, class Tp>
    inline void 
        uninitialized_fill_n(ForwardIt first, Size n, const T& x, Tp* ptr) {
            typedef typename __type_traits<Tp>::is_POD_type is_POD_type;
            uninitialized_fill_n_aux(first, n, x, is_POD_type());
    }
    template<class ForwardIt, class Size, class T>
    inline void
        uninitialized_fill_n(ForwardIt first, Size n, const T& x) {
            uninitialized_fill_n(first, n, x, value_type(first));
    }
    
    
}

#endif // __UNINITIALIZED_H__
