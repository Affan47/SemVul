static void rtl8139_reset(DeviceState *d)
{
    RTL8139State *s = RTL8139(d);
    int i;


    memcpy(s->phys, s->conf.macaddr.a, 6);
    qemu_format_nic_info_str(qemu_get_queue(s->nic), s->phys);


    s->IntrStatus = 0;
    s->IntrMask = 0;

    rtl8139_update_irq(s);


    for (i = 0; i < 4; ++i)
    {
        s->TxStatus[i] = TxHostOwns;
    }

    s->currTxDesc = 0;
    s->currCPlusRxDesc = 0;
    s->currCPlusTxDesc = 0;

    s->RxRingAddrLO = 0;
    s->RxRingAddrHI = 0;

    s->RxBuf = 0;

    rtl8139_reset_rxring(s, 8192);


    s->TxConfig = 0;

#if 0

    s->clock_enabled = 0;
#else
    s->TxConfig |= HW_REVID(1, 1, 1, 0, 1, 1, 0);
    s->clock_enabled = 1;
#endif

    s->bChipCmdState = CmdReset; ;


    s->Config0 = 0x0;
    s->Config1 = 0xC;
    s->Config3 = 0x1;
    s->Config5 = 0x0;

    s->CpCmd   = 0x0;
    s->cplus_enabled = 0;


    s->BasicModeCtrl = 0x1000;

    rtl8139_reset_phy(s);


    s->TCTR = 0;
    s->TimerInt = 0;
    s->TCTR_base = 0;
    rtl8139_set_next_tctr_time(s);


    RTL8139TallyCounters_clear(&s->tally_counters);
}
