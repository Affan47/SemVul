int ext_coal_sdma_tx_descs(struct hfi1_devdata *dd, struct sdma_txreq *tx,
			   int type, void *kvaddr, struct page *page,
			   unsigned long offset, u16 len)
{
	int pad_len, rval;
	dma_addr_t addr;

	rval = _extend_sdma_tx_descs(dd, tx);
	if (rval) {
		__sdma_txclean(dd, tx);
		return rval;
	}


	if (tx->coalesce_buf) {
		if (type == SDMA_MAP_NONE) {
			__sdma_txclean(dd, tx);
			return -EINVAL;
		}

		if (type == SDMA_MAP_PAGE) {
			kvaddr = kmap(page);
			kvaddr += offset;
		} else if (WARN_ON(!kvaddr)) {
			__sdma_txclean(dd, tx);
			return -EINVAL;
		}

		memcpy(tx->coalesce_buf + tx->coalesce_idx, kvaddr, len);
		tx->coalesce_idx += len;
		if (type == SDMA_MAP_PAGE)
			kunmap(page);


		if (tx->tlen - tx->coalesce_idx)
			return 0;


		pad_len = tx->packet_len & (sizeof(u32) - 1);
		if (pad_len) {
			pad_len = sizeof(u32) - pad_len;
			memset(tx->coalesce_buf + tx->coalesce_idx, 0, pad_len);

			tx->packet_len += pad_len;
			tx->tlen += pad_len;
		}


		addr = dma_map_single(&dd->pcidev->dev,
				      tx->coalesce_buf,
				      tx->tlen,
				      DMA_TO_DEVICE);

		if (unlikely(dma_mapping_error(&dd->pcidev->dev, addr))) {
			__sdma_txclean(dd, tx);
			return -ENOSPC;
		}


		tx->desc_limit = MAX_DESC;
		return _sdma_txadd_daddr(dd, SDMA_MAP_SINGLE, tx,
					 addr, tx->tlen);
	}

	return 1;
}
