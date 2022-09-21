/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserverd
*/

#include "mem.h"
#include "bitmap.h"

#define INDEX_FROM_BIT(a) (a/32)
#define OFFSET_FROM_BIT(a) (a%32)

bitmap_t bitmap_create(u32 *arr, int bits) {
    bitmap_t res;
    bitmap_init(&res, arr, bits);
    return res;
}

void bitmap_init(bitmap_t *bitmap, u32 *arr, int bits) {
    bitmap->bits = bits;
    bitmap->arr_size = INDEX_FROM_BIT(bits);
    if (arr == nullptr) {
        arr = (u32 *) malloc(bitmap->arr_size * 4);
        bitmap->alloc_arr = true;
    } else {
        bitmap->alloc_arr = false;
    }

    for (u32 i = 0; i < bitmap->arr_size; i++) {
        arr[i] = 0;
    }
    bitmap->arr = arr;
}

void bitmap_set(bitmap_t *bitmap, u32 bit) {
    u32 index = INDEX_FROM_BIT(bit);
    u32 offset = OFFSET_FROM_BIT(bit);
    bitmap->arr[index] |= (0x1 << offset);
}

void bitmap_clearb(bitmap_t *bitmap, u32 bit) {
    u32 index = INDEX_FROM_BIT(bit);
    u32 offset = OFFSET_FROM_BIT(bit);
    bitmap->arr[index] &= ~(0x1 << offset);
}

bool bitmap_find_first(bitmap_t *bitmap, u32 *bit) {
    u32 i, j;
    for (i = 0; i < bitmap->arr_size; i++) {
        u32 element = bitmap->arr[i];
        if (element != 0xFFFFFFFF) {
            for (j = 0; j < 32; j++) {
                if (!(element & (0x1 << j))) {
                    *bit = i * 32 + j;
                    return true;
                }
            }
        }
    }
    return false;
}

bool bitmap_alloc_first(bitmap_t *bitmap, u32 *bit) {
    bool suc = bitmap_find_first(bitmap, bit);
    if (!suc) return false;
    bitmap_set(bitmap, *bit);
    return true;
}

void bitmap_clear(bitmap_t *bitmap) {
    for (u32 i = 0; i < bitmap->arr_size; i++) bitmap->arr[i] = 0;
}

bool bitmap_expand(bitmap_t *bitmap, u32 size) {
    u32 new_size = size;
    u32 new_arr_size = INDEX_FROM_BIT(size);
    u32 *arr = (u32*) malloc(new_arr_size*4);
    for (i32 i = 0; i < new_arr_size; i++) arr[i] = 0;
    for (i32 i = 0; i < bitmap->arr_size; i++) arr[i] = bitmap->arr[i];
    if (bitmap->alloc_arr) free(bitmap->arr);
    bitmap->bits = new_size;
    bitmap->arr_size = new_arr_size;
    bitmap->alloc_arr = true;
    bitmap->arr = arr;
    return true;
}

void bitmap_destroy(bitmap_t *bitmap) {
    if (bitmap->alloc_arr) free(bitmap->arr);
}