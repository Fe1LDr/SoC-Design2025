/// Copyright by Syntacore LLC © 2016, 2017. See LICENSE for details
/// @file       <csr.h>
/// Architecture specific CSR's defs and inlines

#ifndef SCR_CSR_H
#define SCR_CSR_H

#include <stdbool.h>
#include <stdint.h>

#define __xstringify(s) __stringify(s)
#define __stringify(s) #s

#ifdef read_csr
#undef read_csr
#endif

#ifdef write_csr
#undef write_csr
#endif

#ifdef swap_csr
#undef swap_csr
#endif

#ifdef set_csr
#undef set_csr
#endif

#ifdef clear_csr
#undef clear_csr
#endif

#ifdef rdtime
#undef rdtime
#endif

#ifdef rdcycle
#undef rdcycle
#endif

#ifdef rdinstret
#undef rdinstret
#endif

#define MIE_MEIE (1L << 11)  // external
#define MIE_MTIE (1L << 7)   // timer
#define MIE_MSIE (1L << 3)   // software
#define MIE_NONE (0)         // disable

#define MSTATUS_MPP_MASK (3L << 11)  // previous mode.
#define MSTATUS_MPP_M (3L << 11)
#define MSTATUS_MPP_S (1L << 11)
#define MSTATUS_MPP_U (0L << 11)
#define MSTATUS_MIE (1L << 3)
#define MSTATUS_SIE (1L << 1)

#define read_csr(reg)                                              \
    ({                                                             \
        unsigned long __tmp;                                       \
        asm volatile("csrr %0, " __xstringify(reg) : "=r"(__tmp)); \
        __tmp;                                                     \
    })

#define write_csr(reg, val)                                              \
    do {                                                                 \
        if (__builtin_constant_p(val) && (val) == 0)                     \
            asm volatile("csrw " __xstringify(reg) ", zero" : :);        \
        else if (__builtin_constant_p(val) && (unsigned long)(val) < 32) \
            asm volatile("csrw " __xstringify(reg) ", %0" : : "i"(val)); \
        else                                                             \
            asm volatile("csrw " __xstringify(reg) ", %0" : : "r"(val)); \
    } while (0)

#define swap_csr(reg, val)                                                                \
    ({                                                                                    \
        unsigned long __tmp;                                                              \
        if (__builtin_constant_p(val) && (val) == 0)                                      \
            asm volatile("csrrw %0, " __xstringify(reg) ", zero" : "=r"(__tmp) :);        \
        else if (__builtin_constant_p(val) && (unsigned long)(val) < 32)                  \
            asm volatile("csrrw %0, " __xstringify(reg) ", %1" : "=r"(__tmp) : "i"(val)); \
        else                                                                              \
            asm volatile("csrrw %0, " __xstringify(reg) ", %1" : "=r"(__tmp) : "r"(val)); \
        __tmp;                                                                            \
    })

#define set_csr(reg, bit)                                                                 \
    ({                                                                                    \
        unsigned long __tmp;                                                              \
        if (__builtin_constant_p(bit) && (bit) < 32)                                      \
            asm volatile("csrrs %0, " __xstringify(reg) ", %1" : "=r"(__tmp) : "i"(bit)); \
        else                                                                              \
            asm volatile("csrrs %0, " __xstringify(reg) ", %1" : "=r"(__tmp) : "r"(bit)); \
        __tmp;                                                                            \
    })

#define clear_csr(reg, bit)                                                               \
    ({                                                                                    \
        unsigned long __tmp;                                                              \
        if (__builtin_constant_p(bit) && (bit) < 32)                                      \
            asm volatile("csrrc %0, " __xstringify(reg) ", %1" : "=r"(__tmp) : "i"(bit)); \
        else                                                                              \
            asm volatile("csrrc %0, " __xstringify(reg) ", %1" : "=r"(__tmp) : "r"(bit)); \
        __tmp;                                                                            \
    })

#define rdtime() read_csr(time)
#define rdcycle() read_csr(cycle)
#define rdinstret() read_csr(instret)

static inline unsigned long __attribute__((const)) hartid() {
    unsigned long res;
    asm("csrr %0, mhartid" : "=r"(res));
    return res;
}

static inline unsigned long __attribute__((const)) impid() {
    unsigned long res;
    asm("csrr %0, mimpid" : "=r"(res));
    return res;
}

#endif  // SCR_CSR_H
