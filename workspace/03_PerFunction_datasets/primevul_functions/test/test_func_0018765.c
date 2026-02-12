AddressSpace *cpu_get_address_space(CPUState *cpu, int asidx)
{

    return cpu->cpu_ases[0].as;
}
