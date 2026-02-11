mask_to_cpu_set(const char *mask_string, PLPA_NAME(cpu_set_t) *cpu_set)
{
    size_t i;
    unsigned int mask_value;

    PLPA_CPU_ZERO(cpu_set);
    sscanf(mask_string, "%x", &mask_value);
    for (i = 0; i < sizeof(mask_value) * 8; ++i) {
        if (0 != (mask_value & (1u << i))) {
            PLPA_CPU_SET(i, cpu_set);
        }
    }

    return 0;
}
