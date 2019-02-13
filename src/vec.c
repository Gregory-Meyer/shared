#include "vec.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define DEFAULT_CAPACITY 8

typedef struct Vector {
    size_t len;
    size_t capacity;
    int data[];
} Vector;

static const Vector* as_vec(const void *self) {
    assert(self);

    return (const Vector*) self;
}

static Vector* as_vec_mut(void *self) {
    assert(self);

    return (Vector*) self;
}

void* Vec_new(void) {
    Vector *const self = malloc(sizeof(Vector) + sizeof(int) * DEFAULT_CAPACITY);

    if (!self) {
        return NULL;
    }

    self->len = 0;
    self->capacity = DEFAULT_CAPACITY;

    return self;
}

void Vec_delete(void *self) {
    free(self);
}

void* Vec_push(void *self_v, int value) {
    Vector *self = as_vec_mut(self_v);

    if (self->len == self->capacity) {
        const size_t new_capacity = (self->capacity + 1) * 3 / 2;
        self = realloc(self, sizeof(Vector) + sizeof(int) * new_capacity);

        if (!self) {
            return NULL;
        }

        self->capacity = new_capacity;
    }

    self->data[self->len] = value;
    ++self->len;

    return self;
}

int Vec_pop(void *self_v) {
    Vector *const self = as_vec_mut(self_v);

    if (self->len == 0) {
        return 0;
    }

    --self->len;

    return 1;
}

size_t Vec_len(const void *self) {
    return as_vec(self)->len;
}

const int* Vec_get(const void *self_v, size_t index) {
    const Vector *const self = as_vec(self_v);

    if (index > self->len) {
        return NULL;
    }

    return &self->data[index];
}

int* Vec_get_mut(void *self_v, size_t index) {
    Vector *const self = as_vec_mut(self_v);

    if (index > self->len) {
        return NULL;
    }

    return &self->data[index];
}

const int* Vec_front(const void *self_v) {
    const Vector *const self = as_vec(self_v);

    if (self->len == 0) {
        return NULL;
    }

    return &self->data[0];
}

int* Vec_front_mut(void *self_v) {
    Vector *const self = as_vec_mut(self_v);

    if (self->len == 0) {
        return NULL;
    }

    return &self->data[0];
}

const int* Vec_back(const void *self_v) {
    const Vector *const self = as_vec(self_v);

    if (self->len == 0) {
        return NULL;
    }

    return &self->data[self->len - 1];
}

int* Vec_back_mut(void *self_v) {
    Vector *const self = as_vec_mut(self_v);

    if (self->len == 0) {
        return NULL;
    }

    return &self->data[self->len - 1];
}

void Vec_clear(void *self_v) {
    as_vec_mut(self_v)->len = 0;
}
