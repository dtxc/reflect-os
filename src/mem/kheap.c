#include <kheap.h>

extern u32 end;
u32 placement_addr = (u32) &end;

u32 kmalloc_int(u32 sz, int align, u32 *phy) {
    if (align == 1 && (placement_addr & 0xFFFFF000)) {
        placement_addr &= 0xFFFFF000;
        placement_addr += 0x1000;
    }

    if (phy) {
        *phy = placement_addr;
    }

    u32 tmp = placement_addr;
    placement_addr += sz;
    return tmp;
}

u32 kmalloc_a(u32 sz) {
    return kmalloc_int(sz, 1, 0);
}

u32 kmalloc_p(u32 sz, u32 *phy) {
    return kmalloc_int(sz, 0, phy);
}

u32 kmalloc_ap(u32 sz, u32 *phy) {
    return kmalloc_int(sz, 1, phy);
}

u32 kmalloc(u32 sz) {
    return kmalloc_int(sz, 0, 0);
}