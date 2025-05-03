#include "mem_access.h"

void write_mem_32(uint32_t* addr, int value) {
    volatile int* const __ptr = (volatile int*)(addr);
    *__ptr                    = value;
};

int read_mem_32(const uint32_t* addr) {
    const volatile int* const __ptr = (const volatile int*)(addr);
    const int __value               = *__ptr;
    return __value;
};

static char abs(char a, char b) {
    return (a < b) ? b - a : a - b;
}

int cmpbuf(int* src, int* dst, int size) {
    char* srcb = (char*)src;
    char* dstb = (char*)dst;
    for (int i = 0; i < size; i++) {
        if (abs(srcb[i], dstb[i]) > 16) {
            return 1;
        }
    }
    return 0;
}
