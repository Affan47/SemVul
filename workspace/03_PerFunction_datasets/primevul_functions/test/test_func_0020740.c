static void sungem_tx_kick(SunGEMState *s)
{
    PCIDevice *d = PCI_DEVICE(s);
    uint32_t comp, kick;
    uint32_t txdma_cfg, txmac_cfg, ints;
    uint64_t dbase;

    trace_sungem_tx_kick();


    txdma_cfg = s->txdmaregs[TXDMA_CFG >> 2];
    txmac_cfg = s->macregs[MAC_TXCFG >> 2];
    if (!(txdma_cfg & TXDMA_CFG_ENABLE) ||
        !(txmac_cfg & MAC_TXCFG_ENAB)) {
        trace_sungem_tx_disabled();
        return;
    }


    dbase = s->txdmaregs[TXDMA_DBHI >> 2];
    dbase = (dbase << 32) | s->txdmaregs[TXDMA_DBLOW >> 2];

    comp = s->txdmaregs[TXDMA_TXDONE >> 2] & s->tx_mask;
    kick = s->txdmaregs[TXDMA_KICK >> 2] & s->tx_mask;

    trace_sungem_tx_process(comp, kick, s->tx_mask + 1);


    while (comp != kick) {
        struct gem_txd desc;


        pci_dma_read(d, dbase + comp * sizeof(desc), &desc, sizeof(desc));


        desc.control_word = le64_to_cpu(desc.control_word);
        desc.buffer = le64_to_cpu(desc.buffer);
        trace_sungem_tx_desc(comp, desc.control_word, desc.buffer);


        sungem_process_tx_desc(s, &desc);


        ints = GREG_STAT_TXDONE;
        if (desc.control_word & TXDCTRL_INTME) {
            ints |= GREG_STAT_TXINTME;
        }
        sungem_update_status(s, ints, true);


        comp = (comp + 1) & s->tx_mask;
        s->txdmaregs[TXDMA_TXDONE >> 2] = comp;
    }


    sungem_update_status(s, GREG_STAT_TXALL, true);
}
