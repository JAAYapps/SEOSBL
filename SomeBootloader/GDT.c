#include "GDT.h"
#include "common.h"

struct GDTEntry
{
    UINT16    limit_low;
    UINT16    base_low;
    UINT8     base_mid;
    UINT8     access;
    UINT8     granularity;
    UINT8     base_high;
} __attribute__((__packed__));

struct GDTRegister
{
    UINT16    limit;
    UINT64    base;
} __attribute__((__packed__));

static struct {
    struct GDTEntry entry[5];
} __attribute__((__packed__)) gdt;

static struct GDTRegister GDTReg;

void gdt_init() {
    gdt.entry[0].limit_low = 0;
    gdt.entry[0].base_low = 0;
    gdt.entry[0].base_mid = 0;
    gdt.entry[0].access = 0;
    gdt.entry[0].granularity = 0;
    gdt.entry[0].base_high = 0;

    gdt.entry[1].limit_low = 0;
    gdt.entry[1].base_low = 0;
    gdt.entry[1].base_mid = 0;
    gdt.entry[1].access = 0b10011010;
    gdt.entry[1].granularity = 0b00100000;
    gdt.entry[1].base_high = 0;

    gdt.entry[2].limit_low = 0;
    gdt.entry[2].base_low = 0;
    gdt.entry[2].base_mid = 0;
    gdt.entry[2].access = 0b10010010;
    gdt.entry[2].granularity = 0;
    gdt.entry[2].base_high = 0;

    gdt.entry[3].limit_low = 0;
    gdt.entry[3].base_low = 0;
    gdt.entry[3].base_mid = 0;
    gdt.entry[3].access = 0b11111010;
    gdt.entry[3].granularity = 0b00100000;
    gdt.entry[3].base_high = 0;

    gdt.entry[4].limit_low = 0;
    gdt.entry[4].base_low = 0;
    gdt.entry[4].base_mid = 0;
    gdt.entry[4].access = 0b11110010;
    gdt.entry[4].granularity = 0;
    gdt.entry[4].base_high = 0;

    GDTReg.limit = (UINT16) sizeof(gdt) - 1;
    GDTReg.base = (UINT64) &gdt;

    __asm__ __volatile__("lgdt %0" :: "m"(GDTReg) : "memory");
	
	__asm__ __volatile__(
        "push %0\n\t"
        "push $1f\n\t"
        "lretq\n\t"
        "1:\n\t"
        "mov %1, %%ds\n\t"
        "mov %1, %%es\n\t"
        "mov %1, %%fs\n\t"
        "mov %1, %%gs\n\t"
        "mov %1, %%ss\n\t"
        :: "rmi"(0x08), "rm"(0x10)
        : "memory"
    );
}