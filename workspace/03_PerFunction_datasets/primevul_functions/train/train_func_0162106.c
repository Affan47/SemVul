static void gic_set_priority_mask(GICState *s, int cpu, uint8_t pmask,
                                  MemTxAttrs attrs)
{
    if (gic_cpu_ns_access(s, cpu, attrs)) {
        if (s->priority_mask[cpu] & 0x80) {

            pmask = 0x80 | (pmask >> 1);
        } else {

            return;
        }
    }
    s->priority_mask[cpu] = pmask & gic_fullprio_mask(s, cpu);
}
