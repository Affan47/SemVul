static void gic_complete_irq(GICState *s, int cpu, int irq, MemTxAttrs attrs)
{
    int cm = 1 << cpu;
    int group;

    DPRINTF("EOI %d\n", irq);
    if (gic_is_vcpu(cpu)) {


        bool prio_drop = s->running_priority[cpu] < 0x100;

        if (irq >= GIC_MAXIRQ) {

            return;
        }

        gic_drop_prio(s, cpu, 0);

        if (!gic_eoi_split(s, cpu, attrs)) {
            bool valid = gic_virq_is_valid(s, irq, cpu);
            if (prio_drop && !valid) {


                int rcpu = gic_get_vcpu_real_id(cpu);
                s->h_hcr[rcpu] += 1 << R_GICH_HCR_EOICount_SHIFT;
            } else if (valid) {
                gic_clear_active(s, irq, cpu);
            }
        }

        gic_update_virt(s);
        return;
    }

    if (irq >= s->num_irq) {


        return;
    }
    if (s->running_priority[cpu] == 0x100) {
        return;
    }

    if (s->revision == REV_11MPCORE) {


        if (!GIC_DIST_TEST_EDGE_TRIGGER(irq) && GIC_DIST_TEST_ENABLED(irq, cm)
            && GIC_DIST_TEST_LEVEL(irq, cm)
            && (GIC_DIST_TARGET(irq) & cm) != 0) {
            DPRINTF("Set %d pending mask %x\n", irq, cm);
            GIC_DIST_SET_PENDING(irq, cm);
        }
    }

    group = gic_has_groups(s) && gic_test_group(s, irq, cpu);

    if (gic_cpu_ns_access(s, cpu, attrs) && !group) {
        DPRINTF("Non-secure EOI for Group0 interrupt %d ignored\n", irq);
        return;
    }


    gic_drop_prio(s, cpu, group);


    if (!gic_eoi_split(s, cpu, attrs)) {
        gic_clear_active(s, irq, cpu);
    }
    gic_update(s);
}
