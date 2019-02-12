#ifndef VEC_H
#define VEC_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* Vec_new(void);

void Vec_delete(void *self);

void* Vec_push(void *self, int value);

int Vec_pop(void *self);

size_t Vec_len(const void *self);

const int* Vec_get(const void *self, size_t index);

int* Vec_get_mut(void *self, size_t index);

const int* Vec_front(const void *self);

int* Vec_front_mut(void *self);

const int* Vec_back(const void *self);

int* Vec_back_mut(void *self);

void Vec_clear(void *self);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
