#include "vec_wrapper.h"

#include <mutex>
#include <stdexcept>
#include <unordered_map>
#include <utility>

#include <dlfcn.h>

template <typename F>
F* load_fn(void *lib, const char *name) {
    F *const addr = reinterpret_cast<F*>(dlsym(lib, name));

    if (!addr) {
        throw std::runtime_error("load_fn");
    }

    return addr;
}

const Vec::Vtbl& Vec::get_vtbl(const std::string &filename) {
    struct VtblMap {
        ~VtblMap() {
            for ([[maybe_unused]] auto &[_name, lib_vtbl] : vtbls) {
                dlclose(lib_vtbl.first);
            }
        }

        std::mutex mtx;
        std::unordered_map<std::string, std::pair<void*, Vtbl>> vtbls;
    };

    static VtblMap map;

    const std::scoped_lock lck(map.mtx);

    const auto iter = map.vtbls.find(filename);

    if (iter != map.vtbls.end()) {
        return iter->second.second;
    }

    void *const lib = dlopen(filename.c_str(), RTLD_NOW | RTLD_LOCAL);

    if (!lib) {
        throw std::runtime_error("Vec::get_vtbl");
    }

    Vtbl vtbl;

    vtbl.new_fn = load_fn<void* ()>(lib, "Vec_new");
    vtbl.delete_fn = load_fn<void (void*)>(lib, "Vec_delete");
    vtbl.push_fn = load_fn<void* (void*, int)>(lib, "Vec_push");
    vtbl.pop_fn = load_fn<int (void*)>(lib, "Vec_pop");
    vtbl.len_fn = load_fn<std::size_t (const void*)>(lib, "Vec_len");
    vtbl.get_fn = load_fn<const int* (const void*, std::size_t)>(lib, "Vec_get");
    vtbl.get_mut_fn = load_fn<int* (void*, std::size_t)>(lib, "Vec_get_mut");
    vtbl.front_fn = load_fn<const int* (const void*)>(lib, "Vec_front");
    vtbl.front_mut_fn = load_fn<int* (void*)>(lib, "Vec_front_mut");
    vtbl.back_fn = load_fn<const int* (const void*)>(lib, "Vec_back");
    vtbl.back_mut_fn = load_fn<int* (void*)>(lib, "Vec_back_mut");
    vtbl.clear_fn = load_fn<void (void*)>(lib, "Vec_clear");

    return map.vtbls.emplace_hint(iter, filename, std::make_pair(lib, vtbl))->second.second;
}

Vec::Vec(const std::string &filename) : vtbl_(&get_vtbl(filename)), obj_(vtbl_->new_fn()) {
    if (!obj_) {
        throw std::bad_alloc();
    }
}

Vec::~Vec() {
    vtbl_->delete_fn(obj_);
}

void Vec::push_back(int value) {
    void *const new_obj = vtbl_->push_fn(obj_, value);

    if (!new_obj) {
        throw std::bad_alloc();
    }

    obj_ = new_obj;
}

bool Vec::pop_back() {
    return vtbl_->pop_fn(obj_);
}

std::size_t Vec::size() const noexcept {
    return vtbl_->len_fn(obj_);
}

int& Vec::operator[](std::size_t index) {
    int *const maybe_value = vtbl_->get_mut_fn(obj_, index);

    if (!maybe_value) {
        throw std::out_of_range("Vec::operator[]");
    }

    return *maybe_value;
}

const int& Vec::operator[](std::size_t index) const {
    const int *const maybe_value = vtbl_->get_mut_fn(obj_, index);

    if (!maybe_value) {
        throw std::out_of_range("Vec::operator[] const");
    }

    return *maybe_value;
}

int& Vec::front() {
    int *const maybe_front = vtbl_->front_mut_fn(obj_);

    if (!maybe_front) {
        throw std::out_of_range("Vec::front()");
    }

    return *maybe_front;
}

const int& Vec::front() const {
    const int *const maybe_front = vtbl_->front_fn(obj_);

    if (!maybe_front) {
        throw std::out_of_range("Vec::front() const");
    }

    return *maybe_front;
}

int& Vec::back() {
    int *const maybe_back = vtbl_->back_mut_fn(obj_);

    if (!maybe_back) {
        throw std::out_of_range("Vec::back()");
    }

    return *maybe_back;
}

const int& Vec::back() const {
    const int *const maybe_back = vtbl_->back_fn(obj_);

    if (!maybe_back) {
        throw std::out_of_range("Vec::back() const");
    }

    return *maybe_back;
}
