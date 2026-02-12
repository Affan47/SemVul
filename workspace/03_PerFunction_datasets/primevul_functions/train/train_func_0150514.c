static int cpu_common_post_load(void *opaque, int version_id)
{
    CPUState *cpu = opaque;


    cpu->interrupt_request &= ~0x01;
    tlb_flush(cpu, 1);

    return 0;
}
