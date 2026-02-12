static void sungem_mmio_mac_write(void *opaque, hwaddr addr, uint64_t val,
                                  unsigned size)
{
    SunGEMState *s = opaque;

    if (!(addr <= 0x134)) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "Write to unknown MAC register 0x%"HWADDR_PRIx"\n",
                      addr);
        return;
    }

    trace_sungem_mmio_mac_write(addr, val);


    switch (addr) {

    case MAC_TXRST:
    case MAC_RXRST:
    case MAC_TXSTAT:
    case MAC_RXSTAT:
    case MAC_CSTAT:
    case MAC_PATMPS:
    case MAC_SMACHINE:
        return;
    case MAC_MINFSZ:

        val &= 0x3ff;
        break;
    }

    s->macregs[addr >> 2] = val;


    switch (addr) {
    case MAC_TXMASK:
    case MAC_RXMASK:
    case MAC_MCMASK:
        sungem_eval_cascade_irq(s);
        break;
    case MAC_RXCFG:
        sungem_update_masks(s);
        if ((s->macregs[MAC_RXCFG >> 2] & MAC_RXCFG_ENAB) != 0 &&
            (s->rxdmaregs[RXDMA_CFG >> 2] & RXDMA_CFG_ENABLE) != 0) {
            qemu_flush_queued_packets(qemu_get_queue(s->nic));
        }
        break;
    }
}
