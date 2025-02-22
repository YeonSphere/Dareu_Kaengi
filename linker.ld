OUTPUT_FORMAT("elf64-x86-64")
ENTRY(main)

MEMORY
{
    RAM (rx) : ORIGIN = 0x100000, LENGTH = 512M
}

SECTIONS
{
    . = 0x100000; /* Start address for the kernel */
    
    .text : {
        *(.text.startup)
        *(.text.kernel)
        *(.text.boot)
        *(.text.idt)
        *(.text.gdt)
        *(.text.tss)
    } > RAM
    
    .data : {
        *(.data.kernel)
        *(.data.boot)
        *(.data.idt)
        *(.data.gdt)
        *(.data.tss)
    } > RAM
    
    .bss : {
        *(.bss.kernel)
        *(.bss.boot)
        *(.bss.idt)
        *(.bss.gdt)
        *(.bss.tss)
    } > RAM
    
    .rodata : {
        *(.rodata.kernel)
        *(.rodata.boot)
        *(.rodata.idt)
        *(.rodata.gdt)
        *(.rodata.tss)
    } > RAM
}
