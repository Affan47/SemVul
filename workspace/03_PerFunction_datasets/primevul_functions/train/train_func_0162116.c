static uint8_t gic_get_running_priority(GICState *s, int cpu, MemTxAttrs attrs)
{
    if ((s->revision != REV_11MPCORE) && (s->running_priority[cpu] > 0xff)) {

        return 0xff;
    }

    if (gic_cpu_ns_access(s, cpu, attrs)) {
        if (s->running_priority[cpu] & 0x80) {


            return s->running_priority[cpu] << 1;
        } else {

            return 0;
        }
    } else {
        return s->running_priority[cpu];
    }
}
