static void sungem_process_tx_desc(SunGEMState *s, struct gem_txd *desc)
{
    PCIDevice *d = PCI_DEVICE(s);
    uint32_t len;


    if (desc->control_word & TXDCTRL_SOF) {
        if (s->tx_first_ctl) {
            trace_sungem_tx_unfinished();
        }
        s->tx_size = 0;
        s->tx_first_ctl = desc->control_word;
    }


    len = desc->control_word & TXDCTRL_BUFSZ;


    if ((s->tx_size + len) > MAX_PACKET_SIZE) {
        trace_sungem_tx_overflow();
        len = MAX_PACKET_SIZE - s->tx_size;
    }


    pci_dma_read(d, desc->buffer, &s->tx_data[s->tx_size], len);
    s->tx_size += len;


    if (desc->control_word & TXDCTRL_EOF) {
        trace_sungem_tx_finished(s->tx_size);


        if (s->tx_first_ctl & TXDCTRL_CENAB) {
            sungem_do_tx_csum(s);
        }


        sungem_send_packet(s, s->tx_data, s->tx_size);


        s->tx_size = 0;
        s->tx_first_ctl = 0;
    }
}
