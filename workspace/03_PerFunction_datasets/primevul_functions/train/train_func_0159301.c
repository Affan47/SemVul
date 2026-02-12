static void qxl_send_events(PCIQXLDevice *d, uint32_t events)
{
    uint32_t old_pending;
    uint32_t le_events = cpu_to_le32(events);

    trace_qxl_send_events(d->id, events);
    if (!qemu_spice_display_is_running(&d->ssd)) {

        fprintf(stderr, "%s: spice-server bug: guest stopped, ignoring\n",
                __func__);
        trace_qxl_send_events_vm_stopped(d->id, events);
        return;
    }


#ifdef HAS_ASSUME_ALIGNED
#define ALIGNED_UINT32_PTR(P) ((uint32_t *)__builtin_assume_aligned(P, 4))
#else
#define ALIGNED_UINT32_PTR(P) ((uint32_t *)P)
#endif

    old_pending = atomic_fetch_or(ALIGNED_UINT32_PTR(&d->ram->int_pending),
                                  le_events);
    if ((old_pending & le_events) == le_events) {
        return;
    }
    qemu_bh_schedule(d->update_irq);
}
