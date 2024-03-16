#ifndef __ALLOC_H__
#define __ALLOC_H__

#include <iostream> // for std::cerr
#include <cstdlib> // for malloc / free

namespace MyTinySTL {

#define __THROW_BAD_ALLOC std::cerr << "out of memory" << std::endl; exit(1);

    // 第一级配置器
    class _alloc {
    private:
        // oom: out of memory
        static void* oom_malloc(size_t);
        static void (* oom_handler)();
    public:
        static void* allocate(size_t n) {
            void* result = malloc(n);
            if (result == 0)    result = oom_malloc(n); // 内存不足时，调用 oom_malloc
            return result;
        }

        static void deallocate(void* p, size_t n) {
            free(p);
        }

        // 设置自己的 oom_handler
        static void(* set_malloc_handler(void(*f)()))() { // set_malloc_handler 是一个函数，它的参数是函数指针void(* f)()，返回值是函数指针 void(* )()
            void(* old)() = oom_handler;
            oom_handler = f;
            return old;
        }
    };

    // 初始化 oom_handler 为空
    void (* _alloc::oom_handler)() = 0;
    // 定义 oom_malloc
    void* _alloc::oom_malloc(size_t n) {
        void (* my_oom_handler)();
        void* result;

        for (; ;) { // 不断尝试释放内存，分配内存...
            my_oom_handler = _alloc::oom_handler;
            // 没有定义 oom_handler，抛出异常
            if (0 == my_oom_handler) { __THROW_BAD_ALLOC; }
            (*my_oom_handler)(); // 调用释放内存程序
            result = malloc(n); // 尝试分配内存
            if (result) return result;
        }
    }


    // 第二级配置器
    class alloc {
        private:
            enum { ALIGN = 8 }; // 小型区块上调边界
            enum { MAXBYTES = 128 }; // 小型区块的上限，超过就由 malloc 分配
            enum { FREELISTS = MAXBYTES / ALIGN }; // free_list 的个数
            enum { NOBJS = 20 }; // 每次增加的结点数
        private:
            // free_list 的结点构造
            union obj {
                obj* next;
                char client[1];
            };
            static obj* free_list[FREELISTS];
        private:
            // 内存池
            // 用 char* 而不是 void* 是为了之后 start_free += bytes; 这样的操作
            static char* start_free; // 内存池起始位置
            static char* end_free; // 内存池结束位置
            static size_t heap_size; 
        private:
            // 向上调整为 8 的倍数
            static size_t ROUND_UP(size_t n) {
                return (n + ALIGN - 1) & ~(ALIGN - 1); 
            }
            // ret = 对 8 向上取整后 - 1，决定用第 ret 号 free_list，ret 从 0 开始算
            static size_t FREE_INDEX(size_t n) {
                return (n + ALIGN - 1) / ALIGN - 1;
            }
            // 为 free_list 重新填充内存区块，返回一个大小为 n 的对象的指针，可能加入大小为 n 的区块到 free_list
            static void* refill(size_t n);
            // 配置一块大的空间，可容纳 nobjs 个 bytes 的区块
            // 可能无法配置出足够大的空间，nobjs 可能会降低
            static char* chunk_malloc(size_t bytes, size_t& nobjs);

        public:
            static void* allocate(size_t bytes);
            static void deallocate(void* ptr, size_t bytes);
            static void* reallocate(void* ptr, size_t old_sz, size_t new_sz);
    };

    // alloc 的静态变量的初始化
    char* alloc::start_free = 0;
    char* alloc::end_free = 0;
    size_t alloc::heap_size = 0;
    alloc::obj* alloc::free_list[alloc::FREELISTS] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    void* alloc::allocate(size_t bytes) {
        if (bytes > MAXBYTES) {
            return _alloc::allocate(bytes);
        }
        int index = FREE_INDEX(bytes);
        obj* now_list = free_list[index];

        // 当前 free_list 没有区块
        if (!now_list) {
            return refill(ROUND_UP(bytes));
        } 
        // 当前 free_list 还有区块
        free_list[index] = now_list->next;
        return now_list;
    }

    void alloc::deallocate(void* ptr, size_t bytes) {
        if (bytes > MAXBYTES) {
            free(ptr);
            return;
        }
        int index = FREE_INDEX(bytes);
        obj* node = static_cast<obj*>(ptr);
        node->next = free_list[index];
        free_list[index] = node->next;
    }

    void* alloc::reallocate(void* ptr, size_t old_sz, size_t new_sz) {
        deallocate(ptr, old_sz);
        ptr = allocate(new_sz);
        return ptr;
    }

    void* alloc::refill(size_t bytes) {
        size_t nobjs = NOBJS;
        char* chunk = chunk_malloc(bytes, nobjs);
        obj* result = 0;
        if (nobjs == 1) {
            return chunk;
        } else {
            // 返回一个 bytes 的对象，多余的放在 free_list 下面
            result = (obj*)chunk;

            int index = FREE_INDEX(bytes);
            obj* current_node = 0;
            obj* next_node = 0;
            free_list[index] = next_node = (obj*)(chunk + bytes);
            for (size_t i = 1; ; i++) {
                current_node = next_node;
                next_node = (obj*)((char*)current_node + bytes);
                if (i == nobjs - 1) {
                    current_node->next = 0;
                    break;
                } else {
                    current_node->next = next_node;
                }
            }
            return result;
        }
    }

    // 从内存池中取 nobjs 块大小为 bytes 区块
    // 无法满足的话，nobjs 可能会降低
    char* alloc::chunk_malloc(size_t bytes, size_t& nobjs) {
        char* result = 0;
        size_t bytes_left = end_free - start_free;
        size_t bytes_total_need = nobjs * bytes;

        if (bytes_left >= bytes_total_need) { // 内存池剩余空间满足需要
            result = start_free;
            start_free += bytes;
            return result;
        } else if (bytes_left >= bytes) { // 内存池剩余空间可以满足 1 个及 1 个以上 bytes 大小的区块的需要
            result = start_free;
            nobjs = bytes_left / bytes;
            start_free += nobjs * bytes;
            return result;
        } else {
            if (bytes_left > 0) {
                int index = FREE_INDEX(bytes_left);
                ((obj*)start_free)->next = free_list[index];
                free_list[index] = (obj*)start_free;
            }
            size_t bytes_to_get = bytes * nobjs * 2 + (heap_size >> 4);
            start_free = (char*)malloc(bytes_to_get);
            if (!start_free) { // 堆内存无法满足需要，尝试使用其他 free_list 的区块
                for (int i = bytes; i <= MAXBYTES; i += ALIGN) {
                    int index = FREE_INDEX(i);
                    if (!free_list[index]) {
                        start_free = (char*)free_list[index];
                        free_list[index] = free_list[index]->next;
                        end_free = start_free + i;
                        return chunk_malloc(bytes, nobjs); // 修正 objs
                    }
                }
                // 分配不到堆内存，也没有剩余可以满足需要的 free_list 区块
                end_free = 0;
                // 使用 oom 机制
                start_free = (char*)_alloc::allocate(bytes_to_get);
            }
            end_free = start_free + bytes_to_get;
            heap_size += bytes_to_get;
            return chunk_malloc(bytes, nobjs);
        }
    }
}


#endif // __ALLOC_H_