static void rtl8139_IntrStatus_write(RTL8139State *s, uint32_t val)
{
    DPRINTF("IntrStatus write(w) val=0x%04x\n", val);

#if 0


    return;

#else
    uint16_t newStatus = s->IntrStatus & ~val;


    newStatus = SET_MASKED(newStatus, 0x1e00, s->IntrStatus);


    s->IntrStatus = 0;
    rtl8139_update_irq(s);

    s->IntrStatus = newStatus;
    rtl8139_set_next_tctr_time(s);
    rtl8139_update_irq(s);

#endif
}
