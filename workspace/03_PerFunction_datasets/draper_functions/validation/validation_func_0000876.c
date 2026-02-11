free_rspq_fl(struct adapter *adapter, struct sge_rspq *rspq,
			 struct sge_fl *fl)
{
	struct sge *s = &adapter->sge;
	unsigned int flid = fl ? fl->cntxt_id : 0xffff;

	t4vf_iq_free(adapter, FW_IQ_TYPE_FL_INT_CAP,
		     rspq->cntxt_id, flid, 0xffff);
	dma_free_coherent(adapter->pdev_dev, (rspq->size + 1) * rspq->iqe_len,
			  rspq->desc, rspq->phys_addr);
	netif_napi_del(&rspq->napi);
	rspq->netdev = NULL;
	rspq->cntxt_id = 0;
	rspq->abs_id = 0;
	rspq->desc = NULL;

	if (fl) {
		free_rx_bufs(adapter, fl, fl->avail);
		dma_free_coherent(adapter->pdev_dev,
				  fl->size * sizeof(*fl->desc) + s->stat_len,
				  fl->desc, fl->addr);
		kfree(fl->sdesc);
		fl->sdesc = NULL;
		fl->cntxt_id = 0;
		fl->desc = NULL;
	}
}
