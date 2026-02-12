static void gic_drop_prio(GICState *s, int cpu, int group)
{


    if (gic_is_vcpu(cpu)) {
        int rcpu = gic_get_vcpu_real_id(cpu);

        if (s->h_apr[rcpu]) {

            s->h_apr[rcpu] &= s->h_apr[rcpu] - 1;
        }
    } else {
        int i;

        for (i = 0; i < GIC_NR_APRS; i++) {
            uint32_t *papr = group ? &s->nsapr[i][cpu] : &s->apr[i][cpu];
            if (!*papr) {
                continue;
            }

            *papr &= *papr - 1;
            break;
        }
    }

    s->running_priority[cpu] = gic_get_prio_from_apr_bits(s, cpu);
}
