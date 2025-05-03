#include "irq.h"
#include "csr.h"
#include "mem_access.h"
#include "plic.h"
#include <stdio.h>

bool wfi_reader;
bool wfi_writer;
bool wfi_decode;

void reader_interrupt_callback(void) {
    printf("Reader interrupt arrived.\n");
    wfi_reader = false;
}

void writer_interrupt_callback(void) {
    printf("Writer interrupt arrived.\n");
    wfi_writer = false;
}

void decode_interrupt_callback(void) {
    printf("Decode interrupt arrived.\n");
    wfi_decode = false;
}

void __attribute__((weak)) default_interrupt_callback(int num) {
    printf("Arrived exception on line %d\n", num);
}

void wait_interrupt(int num) {
    uint32_t bitshift = num % 32;
    while (!(read_mem_32((uint32_t*)PLIC_PENDING_ADDR(num)) & (1 << bitshift)));
}

static void plic_enable(uint32_t int_id) {
    uint32_t reg              = int_id / 32;
    uint32_t bitshift         = int_id % 32;
    uint32_t plic_enable_addr = PLIC_ENABLE_ADDR(reg);
    uint32_t enable_reg       = read_mem_32((uint32_t*)plic_enable_addr);
    enable_reg |= (1 << bitshift);
    write_mem_32((uint32_t*)plic_enable_addr, enable_reg);
    write_mem_32((uint32_t*)PLIC_PRIORITY_ADDR(int_id), 0x2);
}

static void __attribute__((aligned(16), interrupt)) default_vector_handler(void) {
    int claim_complete_id = read_mem_32((uint32_t*)PLIC_CLAIM_COMPLETE_ADDR);
    switch (claim_complete_id) {
        case READER_DONE_IRQ_NUM:
            reader_interrupt_callback();
            break;
        case WRITER_DONE_IRQ_NUM:
            writer_interrupt_callback();
            break;
        case DECODE_DONE_IRQ_NUM:
            decode_interrupt_callback();
            break;
        default:
            default_interrupt_callback(claim_complete_id);
            break;
    }
}

static void set_isr_plic() {
    plic_enable(READER_DONE_IRQ_NUM);
    plic_enable(WRITER_DONE_IRQ_NUM);
    plic_enable(DECODE_DONE_IRQ_NUM);
    write_mem_32((uint32_t*)PLIC_THRESHOLD_ADDR, PLIC_BASE_THRESHOLD);
}

void set_isr_routine() {
    const int mie_val = read_csr(mie);
    write_csr(mie, 0);
    write_csr(mtvec, (uintptr_t)(default_vector_handler));
    set_isr_plic();
    const int mstatus_val = read_csr(mstatus);
    write_csr(mstatus, mstatus_val | MSTATUS_MIE);  // MIE
    write_csr(mie, mie_val | MIE_MSIE | MIE_MEIE);
}