#include "stdio.h"


typedef unsigned short  u16;
typedef signed short    s16;
typedef int             s32;
typedef unsigned int    u32;
typedef unsigned long long u64;




u16 cs, ds, ss, es, fs, gs;



void get_segment_registers_info()
{
    asm volatile("mov %%cs, %0" : "=r" (cs));
    asm volatile("mov %%ds, %0" : "=r" (ds));
    asm volatile("mov %%ss, %0" : "=r" (ss));
    asm volatile("mov %%es, %0" : "=r" (es));
    asm volatile("mov %%fs, %0" : "=r" (fs));
    asm volatile("mov %%gs, %0" : "=r" (gs));

    printf("cs :%04x\n", cs);
    printf("ds :%04x\n", ds);
    printf("ss :%04x\n", ss);
    printf("es :%04x\n", es);
    printf("fs :%04x\n", fs);
    printf("gs :%04x\n", gs);
}


int main()
{
    get_segment_registers_info();

    return 0;
}



