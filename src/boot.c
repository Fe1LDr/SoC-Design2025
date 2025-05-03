#include "irq.h"
#include "boot.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    set_isr_routine();
    int ret = sim_main();
    FILE* f = fopen(".exit_code", "w");
    fprintf(f, "%d", ret);
    fclose(f);
    exit(0);
    return 0;
}
