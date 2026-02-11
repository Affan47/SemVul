xgs_isr(bkn_switch_info_t *sinfo)
{
    uint32_t irq_stat;
    int rx_dcbs_done;

    DEV_READ32(sinfo, CMIC_IRQ_STATr, &irq_stat);
    if ((irq_stat & sinfo->irq_mask) == 0) {

        return;
    }
    sinfo->interrupts++;

    DBG_IRQ(("Got interrupt on device %d (0x%08x)\n",
             sinfo->dev_no, irq_stat));

    if (use_napi) {
        bkn_schedule_napi_poll(sinfo);
    } else {
        xgs_irq_mask_set(sinfo, 0);
        do {
            rx_dcbs_done = xgs_do_dma(sinfo, MAX_RX_DCBS);
        } while (rx_dcbs_done);
    }

    xgs_irq_mask_set(sinfo, sinfo->irq_mask);
}
