static uint32_t gic_dist_get_priority(GICState *s, int cpu, int irq,
                                 MemTxAttrs attrs)
{
    uint32_t prio = GIC_DIST_GET_PRIORITY(irq, cpu);

    if (s->security_extn && !attrs.secure) {
        if (!GIC_DIST_TEST_GROUP(irq, (1 << cpu))) {
            return 0;
        }
        prio = (prio << 1) & 0xff;
    }
    return prio & gic_fullprio_mask(s, cpu);
}
