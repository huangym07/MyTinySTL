#ifndef __TYPETRAITS_H__
#define __TYPETRAITS_H__

// 对类型 T 的类型特性萃取
// 对内置类型特化
namespace MyTinySTL
{
    // 用结构体来表示 true 和 false
    struct __true_type{};
    struct __false_type{};

    template<typename T>
    struct __type_traits {
        typedef __true_type this_dummy_member_must_be_first;
        // 暂时不知道这个重定义有什么用，可能是通知编译器这个 __type_traits template 是特殊的

        typedef __false_type    has_trivial_default_constructor;
        typedef __false_type    has_trivial_copy_constructor;
        typedef __false_type    has_trivial_assignment_operator;
        typedef __false_type    has_trivial_destructor;
        typedef __false_type    is_POD_type;
    };

    template<>
    struct __type_traits<char> {
        typedef __true_type    has_trivial_default_constructor;
        typedef __true_type    has_trivial_copy_constructor;
        typedef __true_type    has_trivial_assignment_operator;
        typedef __true_type    has_trivial_destructor;
        typedef __true_type    is_POD_type;
    };

    template<>
    struct __type_traits<unsigned char> {
        typedef __true_type    has_trivial_default_constructor;
        typedef __true_type    has_trivial_copy_constructor;
        typedef __true_type    has_trivial_assignment_operator;
        typedef __true_type    has_trivial_destructor;
        typedef __true_type    is_POD_type;
    };
    
    template<>
    struct __type_traits<signed char> {
        typedef __true_type    has_trivial_default_constructor;
        typedef __true_type    has_trivial_copy_constructor;
        typedef __true_type    has_trivial_assignment_operator;
        typedef __true_type    has_trivial_destructor;
        typedef __true_type    is_POD_type;
    };

    template<>
    struct __type_traits<int> {
        typedef __true_type    has_trivial_default_constructor;
        typedef __true_type    has_trivial_copy_constructor;
        typedef __true_type    has_trivial_assignment_operator;
        typedef __true_type    has_trivial_destructor;
        typedef __true_type    is_POD_type;
    };

    template<>
    struct __type_traits<unsigned int> {
        typedef __true_type    has_trivial_default_constructor;
        typedef __true_type    has_trivial_copy_constructor;
        typedef __true_type    has_trivial_assignment_operator;
        typedef __true_type    has_trivial_destructor;
        typedef __true_type    is_POD_type;
    };

    template<>
    struct __type_traits<long> {
        typedef __true_type    has_trivial_default_constructor;
        typedef __true_type    has_trivial_copy_constructor;
        typedef __true_type    has_trivial_assignment_operator;
        typedef __true_type    has_trivial_destructor;
        typedef __true_type    is_POD_type;
    };

    template<>
    struct __type_traits<unsigned long> {
        typedef __true_type    has_trivial_default_constructor;
        typedef __true_type    has_trivial_copy_constructor;
        typedef __true_type    has_trivial_assignment_operator;
        typedef __true_type    has_trivial_destructor;
        typedef __true_type    is_POD_type;
    };

    template<>
    struct __type_traits<short> {
        typedef __true_type    has_trivial_default_constructor;
        typedef __true_type    has_trivial_copy_constructor;
        typedef __true_type    has_trivial_assignment_operator;
        typedef __true_type    has_trivial_destructor;
        typedef __true_type    is_POD_type;
    };

    template<>
    struct __type_traits<unsigned short> {
        typedef __true_type    has_trivial_default_constructor;
        typedef __true_type    has_trivial_copy_constructor;
        typedef __true_type    has_trivial_assignment_operator;
        typedef __true_type    has_trivial_destructor;
        typedef __true_type    is_POD_type;
    };

    template<>
    struct __type_traits<float> {
        typedef __true_type    has_trivial_default_constructor;
        typedef __true_type    has_trivial_copy_constructor;
        typedef __true_type    has_trivial_assignment_operator;
        typedef __true_type    has_trivial_destructor;
        typedef __true_type    is_POD_type;
    };

    template<>
    struct __type_traits<double> {
        typedef __true_type    has_trivial_default_constructor;
        typedef __true_type    has_trivial_copy_constructor;
        typedef __true_type    has_trivial_assignment_operator;
        typedef __true_type    has_trivial_destructor;
        typedef __true_type    is_POD_type;
    };

    template<>
    struct __type_traits<long double> {
        typedef __true_type    has_trivial_default_constructor;
        typedef __true_type    has_trivial_copy_constructor;
        typedef __true_type    has_trivial_assignment_operator;
        typedef __true_type    has_trivial_destructor;
        typedef __true_type    is_POD_type;
    };

    template<typename T>
    struct __type_traits<T*> {
        typedef __true_type    has_trivial_default_constructor;
        typedef __true_type    has_trivial_copy_constructor;
        typedef __true_type    has_trivial_assignment_operator;
        typedef __true_type    has_trivial_destructor;
        typedef __true_type    is_POD_type;
    };
}

#endif // __TYPETRAITS_H__