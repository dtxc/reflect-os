/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserverd
*/

#pragma once

#include "types.h"

typedef struct {
    u32 *arr;
    u8 alloc_arr;
    int arr_size;
    int bits;
} bitmap_t;

bitmap_t bitmap_create(u32 *arr, int bits);
void bitmap_init(bitmap_t *bitmap, u32 *arr, int bits);
void bitmap_set(bitmap_t *bitmap, u32 bit);
void bitmap_clearb(bitmap_t *bitmap, u32 bit);
void bitmap_clear(bitmap_t *bitmap);
bool bitmap_expand(bitmap_t *bitmap, u32 size);
void bitmap_destroy(bitmap_t *bitmap);
bool bitmap_find_first(bitmap_t *bitmap, u32 *bit);
bool bitmap_alloc_first(bitmap_t *bitmap, u32 *bit);