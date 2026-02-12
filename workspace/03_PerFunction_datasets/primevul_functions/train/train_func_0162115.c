static MemTxResult gic_cpu_read(GICState *s, int cpu, int offset,
                                uint64_t *data, MemTxAttrs attrs)
{
    switch (offset) {
    case 0x00:
        *data = gic_get_cpu_control(s, cpu, attrs);
        break;
    case 0x04:
        *data = gic_get_priority_mask(s, cpu, attrs);
        break;
    case 0x08:
        if (gic_cpu_ns_access(s, cpu, attrs)) {
            if (s->cpu_ctlr[cpu] & GICC_CTLR_CBPR) {

                *data = MIN(s->bpr[cpu] + 1, 7);
            } else {

                *data = s->abpr[cpu];
            }
        } else {
            *data = s->bpr[cpu];
        }
        break;
    case 0x0c:
        *data = gic_acknowledge_irq(s, cpu, attrs);
        break;
    case 0x14:
        *data = gic_get_running_priority(s, cpu, attrs);
        break;
    case 0x18:
        *data = gic_get_current_pending_irq(s, cpu, attrs);
        break;
    case 0x1c:


        if (!gic_has_groups(s) || (gic_cpu_ns_access(s, cpu, attrs))) {
            *data = 0;
        } else {
            *data = s->abpr[cpu];
        }
        break;
    case 0xd0: case 0xd4: case 0xd8: case 0xdc:
    {
        int regno = (offset - 0xd0) / 4;
        int nr_aprs = gic_is_vcpu(cpu) ? GIC_VIRT_NR_APRS : GIC_NR_APRS;

        if (regno >= nr_aprs || s->revision != 2) {
            *data = 0;
        } else if (gic_is_vcpu(cpu)) {
            *data = s->h_apr[gic_get_vcpu_real_id(cpu)];
        } else if (gic_cpu_ns_access(s, cpu, attrs)) {

            *data = gic_apr_ns_view(s, regno, cpu);
        } else {
            *data = s->apr[regno][cpu];
        }
        break;
    }
    case 0xe0: case 0xe4: case 0xe8: case 0xec:
    {
        int regno = (offset - 0xe0) / 4;

        if (regno >= GIC_NR_APRS || s->revision != 2 || !gic_has_groups(s) ||
            gic_cpu_ns_access(s, cpu, attrs) || gic_is_vcpu(cpu)) {
            *data = 0;
        } else {
            *data = s->nsapr[regno][cpu];
        }
        break;
    }
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "gic_cpu_read: Bad offset %x\n", (int)offset);
        *data = 0;
        break;
    }

    trace_gic_cpu_read(gic_is_vcpu(cpu) ? "vcpu" : "cpu",
                       gic_get_vcpu_real_id(cpu), offset, *data);
    return MEMTX_OK;
}
