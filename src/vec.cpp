#include "vec.h"

#include <cassert>
#include <vector>

std::vector<int>& as_vec(void *self) {
    assert(self);

    return *static_cast<std::vector<int>*>(self);
}

const std::vector<int>& as_vec(const void *self) {
    assert(self);

    return *static_cast<const std::vector<int>*>(self);
}

void* Vec_new() {
    return new(std::nothrow) std::vector<int>();
}

void Vec_delete(void *self) {
    delete &as_vec(self);
}

void* Vec_push(void *self, int value) {
    try {
        as_vec(self).push_back(value);
    } catch (...) {
        return nullptr;
    }

    return self;
}

int Vec_pop(void *self) {
    if (as_vec(self).empty()) {
        return false;
    }

    as_vec(self).pop_back();

    return true;
}

std::size_t Vec_len(const void *self) {
    return static_cast<std::size_t>(as_vec(self).size());
}

const int* Vec_get(const void *self, std::size_t index) {
    const auto as_size = static_cast<std::vector<int>::size_type>(index);

    if (as_size > as_vec(self).size()) {
        return nullptr;
    }

    return &as_vec(self)[as_size];
}

int* Vec_get_mut(void *self, std::size_t index) {
    const auto as_size = static_cast<std::vector<int>::size_type>(index);

    if (as_size > as_vec(self).size()) {
        return nullptr;
    }

    return &as_vec(self)[as_size];
}

const int* Vec_front(const void *self) {
    if (as_vec(self).empty()) {
        return nullptr;
    }

    return &as_vec(self).front();
}

int* Vec_front_mut(void *self) {
    if (as_vec(self).empty()) {
        return nullptr;
    }

    return &as_vec(self).front();
}

const int* Vec_back(const void *self) {
    if (as_vec(self).empty()) {
        return nullptr;
    }

    return &as_vec(self).back();
}

int* Vec_back_mut(void *self) {
    if (as_vec(self).empty()) {
        return nullptr;
    }

    return &as_vec(self).back();
}

void Vec_clear(void *self) {
    as_vec(self).clear();
}
