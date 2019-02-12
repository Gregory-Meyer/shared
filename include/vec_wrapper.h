#ifndef VEC_WRAPPER_H
#define VEC_WRAPPER_H

#include <cstddef>
#include <string>

class Vec {
public:
    explicit Vec(const std::string &filename);

    ~Vec();

    void push_back(int value);

    bool pop_back();

    std::size_t size() const noexcept;

    int& operator[](std::size_t index);

    const int& operator[](std::size_t index) const;

    int& front();

    const int& front() const;

    int& back();

    const int& back() const;

private:
    struct Vtbl {
        void* (*new_fn)();
        void (*delete_fn)(void*);
        void* (*push_fn)(void*, int);
        int (*pop_fn)(void*);
        std::size_t (*len_fn)(const void*);
        const int* (*get_fn)(const void*, std::size_t);
        int* (*get_mut_fn)(void*, std::size_t);
        const int* (*front_fn)(const void*);
        int* (*front_mut_fn)(void*);
        const int* (*back_fn)(const void*);
        int* (*back_mut_fn)(void*);
        void (*clear_fn)(void*);
    };

    static const Vtbl& get_vtbl(const std::string &filename);

    const Vtbl *vtbl_;
    void *obj_;
};

#endif
