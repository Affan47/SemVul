vmxnet3_rq_destroy(struct vmxnet3_rx_queue *rq,
			       struct vmxnet3_adapter *adapter)
{
	int i;
	int j;


	for (i = 0; i < 2; i++) {
		if (rq->buf_info[i]) {
			for (j = 0; j < rq->rx_ring[i].size; j++)
				BUG_ON(rq->buf_info[i][j].page != NULL);
		}
	}


	for (i = 0; i < 2; i++) {
		if (rq->rx_ring[i].base) {
			dma_free_coherent(&adapter->pdev->dev,
					  rq->rx_ring[i].size
					  * sizeof(struct Vmxnet3_RxDesc),
					  rq->rx_ring[i].base,
					  rq->rx_ring[i].basePA);
			rq->rx_ring[i].base = NULL;
		}
	}

	if (rq->comp_ring.base) {
		dma_free_coherent(&adapter->pdev->dev, rq->comp_ring.size
				  * sizeof(struct Vmxnet3_RxCompDesc),
				  rq->comp_ring.base, rq->comp_ring.basePA);
		rq->comp_ring.base = NULL;
	}

	if (rq->buf_info[0]) {
		size_t sz = sizeof(struct vmxnet3_rx_buf_info) *
			(rq->rx_ring[0].size + rq->rx_ring[1].size);
		dma_free_coherent(&adapter->pdev->dev, sz, rq->buf_info[0],
				  rq->buf_info_pa);
		rq->buf_info[0] = rq->buf_info[1] = NULL;
	}
}
