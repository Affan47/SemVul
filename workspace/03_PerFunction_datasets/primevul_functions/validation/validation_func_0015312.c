virtio_dev_pktmbuf_alloc(struct virtio_net *dev, struct rte_mempool *mp,
			 uint32_t data_len)
{
	struct rte_mbuf *pkt = rte_pktmbuf_alloc(mp);

	if (unlikely(pkt == NULL)) {
		VHOST_LOG_DATA(ERR,
			"Failed to allocate memory for mbuf.\n");
		return NULL;
	}

	if (rte_pktmbuf_tailroom(pkt) >= data_len)
		return pkt;


	if (dev->extbuf && !virtio_dev_extbuf_alloc(pkt, data_len))
		return pkt;


	if (!dev->linearbuf)
		return pkt;


	rte_pktmbuf_free(pkt);

	return NULL;
}
