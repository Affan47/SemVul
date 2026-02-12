static void gic_deactivate_irq(GICState *s, int cpu, int irq, MemTxAttrs attrs)
{
    int group;

    if (irq >= GIC_MAXIRQ || (!gic_is_vcpu(cpu) && irq >= s->num_irq)) {


        return;
    }

    if (!gic_eoi_split(s, cpu, attrs)) {

        qemu_log_mask(LOG_GUEST_ERROR,
                      "gic_deactivate_irq: GICC_DIR write when EOIMode clear");
        return;
    }

    if (gic_is_vcpu(cpu) && !gic_virq_is_valid(s, irq, cpu)) {


        int rcpu = gic_get_vcpu_real_id(cpu);
        s->h_hcr[rcpu] += 1 << R_GICH_HCR_EOICount_SHIFT;


        gic_update_virt(s);
        return;
    }

    group = gic_has_groups(s) && gic_test_group(s, irq, cpu);

    if (gic_cpu_ns_access(s, cpu, attrs) && !group) {
        DPRINTF("Non-secure DI for Group0 interrupt %d ignored\n", irq);
        return;
    }

    gic_clear_active(s, irq, cpu);
}
