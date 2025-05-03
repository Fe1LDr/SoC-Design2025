#pragma once
#include <stdbool.h>

extern bool wfi_reader;
extern bool wfi_writer;
extern bool wfi_decode;

void reader_interrupt_callback(void);
void writer_interrupt_callback(void);
void decode_interrupt_callback(void);
void default_interrupt_callback(int num);

void set_isr_routine();
