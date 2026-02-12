void dma_complete(struct s_smc *smc, volatile union s_fp_descr *descr, int flag)
{


	if (flag & DMA_WR) {
		skfddi_priv *bp = &smc->os;
		volatile struct s_smt_fp_rxd *r = &descr->r;


		if (r->rxd_os.skb && r->rxd_os.dma_addr) {
			int MaxFrameSize = bp->MaxFrameSize;

			pci_unmap_single(&bp->pdev, r->rxd_os.dma_addr,
					 MaxFrameSize, PCI_DMA_FROMDEVICE);
			r->rxd_os.dma_addr = 0;
		}
	}
}
