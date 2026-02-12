static uint64_t sungem_mmio_mac_read(void *opaque, hwaddr addr, unsigned size)
{
    SunGEMState *s = opaque;
    uint32_t val;

    if (!(addr <= 0x134)) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "Read from unknown MAC register 0x%"HWADDR_PRIx"\n",
                      addr);
        return 0;
    }

    val = s->macregs[addr >> 2];

    trace_sungem_mmio_mac_read(addr, val);

    switch (addr) {
    case MAC_TXSTAT:

        s->macregs[addr >> 2] = 0;
        sungem_update_status(s, GREG_STAT_TXMAC, false);
        break;
    case MAC_RXSTAT:

        s->macregs[addr >> 2] = 0;
        sungem_update_status(s, GREG_STAT_RXMAC, false);
        break;
    case MAC_CSTAT:

        s->macregs[addr >> 2] &= MAC_CSTAT_PTR;
        sungem_update_status(s, GREG_STAT_MAC, false);
        break;
    }

    return val;
}
