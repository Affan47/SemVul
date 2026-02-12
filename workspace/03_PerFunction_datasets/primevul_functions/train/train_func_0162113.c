static uint32_t gic_fullprio_mask(GICState *s, int cpu)
{


    int priBits;

    if (gic_is_vcpu(cpu)) {
        priBits = GIC_VIRT_MAX_GROUP_PRIO_BITS;
    } else {
        priBits = s->n_prio_bits;
    }
    return ~0U << (8 - priBits);
}
