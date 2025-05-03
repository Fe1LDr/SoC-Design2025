#pragma once
#include <stdint.h>

void write_mem_32(uint32_t* addr, int value);
int read_mem_32(const uint32_t* addr);
int cmpbuf(int* src, int* dst, int size);
