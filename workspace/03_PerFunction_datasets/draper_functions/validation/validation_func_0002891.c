mac_drv_clear_txd(struct s_smc *smc)
{
	struct s_smt_tx_queue *queue ;
	struct s_smt_fp_txd volatile *t1 ;
	struct s_smt_fp_txd volatile *t2 = NULL ;
	SMbuf *mb ;
	u_long	tbctrl ;
	int i ;
	int frag_count ;
	int n ;

	NDD_TRACE("THcB",0,0,0) ;
	for (i = QUEUE_S; i <= QUEUE_A0; i++) {
		queue = smc->hw.fp.tx[i] ;
		t1 = queue->tx_curr_get ;
		DB_TX("clear_txd: QUEUE = %d (0=sync/1=async)",i,0,5) ;

		for ( ; ; ) {
			frag_count = 0 ;

			do {
				DRV_BUF_FLUSH(t1,DDI_DMA_SYNC_FORCPU) ;
				DB_TX("check OWN/EOF bit of TxD 0x%x",t1,0,5) ;
				tbctrl = le32_to_cpu(CR_READ(t1->txd_tbctrl));

				if (tbctrl & BMU_OWN || !queue->tx_used){
					DB_TX("End of TxDs queue %d",i,0,4) ;
					goto free_next_queue ;
				}
				t1 = t1->txd_next ;
				frag_count++ ;
			} while (!(tbctrl & BMU_EOF)) ;

			t1 = queue->tx_curr_get ;
			for (n = frag_count; n; n--) {
				tbctrl = le32_to_cpu(t1->txd_tbctrl) ;
				dma_complete(smc,
					(union s_fp_descr volatile *) t1,
					(int) (DMA_RD |
					((tbctrl & BMU_SMT_TX) >> 18))) ;
				t2 = t1 ;
				t1 = t1->txd_next ;
			}

			if (tbctrl & BMU_SMT_TX) {
				mb = get_txd_mb(smc) ;
				smt_free_mbuf(smc,mb) ;
			}
			else {
#ifndef PASS_1ST_TXD_2_TX_COMP
				DB_TX("mac_drv_tx_comp for TxD 0x%x",t2,0,4) ;
				mac_drv_tx_complete(smc,t2) ;
#else
				DB_TX("mac_drv_tx_comp for TxD 0x%x",
					queue->tx_curr_get,0,4) ;
				mac_drv_tx_complete(smc,queue->tx_curr_get) ;
#endif
			}
			queue->tx_curr_get = t1 ;
			queue->tx_free += frag_count ;
			queue->tx_used -= frag_count ;
		}
free_next_queue: ;
	}
	NDD_TRACE("THcE",0,0,0) ;
}
