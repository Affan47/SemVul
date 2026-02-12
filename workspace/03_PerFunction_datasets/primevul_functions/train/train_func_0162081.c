static int gic_get_group_priority(GICState *s, int cpu, int irq)
{


    int bpr;
    uint32_t mask;

    if (gic_has_groups(s) &&
        !(s->cpu_ctlr[cpu] & GICC_CTLR_CBPR) &&
        gic_test_group(s, irq, cpu)) {
        bpr = s->abpr[cpu] - 1;
        assert(bpr >= 0);
    } else {
        bpr = s->bpr[cpu];
    }


    mask = ~0U << ((bpr & 7) + 1);

    return gic_get_priority(s, irq, cpu) & mask;
}
