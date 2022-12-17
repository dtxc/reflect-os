#pragma once

#include <common.h>

u32 kmalloc_int(u32 sz, int align, u32 *phy);
u32 kmalloc_a(u32 sz);
u32 kmalloc_p(u32 sz, u32 *phy);
u32 kmalloc_ap(u32 sz, u32 *phy);
u32 kmalloc(u32 sz);