mwifiex_pcie_send_cmd(struct mwifiex_adapter *adapter, struct sk_buff *skb)
{
	struct pcie_service_card *card = adapter->card;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;
	int ret = 0;
	dma_addr_t cmd_buf_pa, cmdrsp_buf_pa;
	u8 *payload = (u8 *)skb->data;

	if (!(skb->data && skb->len)) {
		mwifiex_dbg(adapter, ERROR,
			    "Invalid parameter in %s <%p, %#x>\n",
			    __func__, skb->data, skb->len);
		return -1;
	}


	if (!card->cmdrsp_buf) {
		mwifiex_dbg(adapter, ERROR,
			    "No response buffer available, send command failed\n");
		return -EBUSY;
	}

	if (!mwifiex_pcie_ok_to_access_hw(adapter))
		mwifiex_pm_wakeup_card(adapter);

	adapter->cmd_sent = true;

	put_unaligned_le16((u16)skb->len, &payload[0]);
	put_unaligned_le16(MWIFIEX_TYPE_CMD, &payload[2]);

	if (mwifiex_map_pci_memory(adapter, skb, skb->len, PCI_DMA_TODEVICE))
		return -1;

	card->cmd_buf = skb;


	skb_get(skb);


	if (card->cmdrsp_buf) {
		cmdrsp_buf_pa = MWIFIEX_SKB_DMA_ADDR(card->cmdrsp_buf);


		if (mwifiex_write_reg(adapter, reg->cmdrsp_addr_lo,
				      (u32)cmdrsp_buf_pa)) {
			mwifiex_dbg(adapter, ERROR,
				    "Failed to write download cmd to boot code.\n");
			ret = -1;
			goto done;
		}


		if (mwifiex_write_reg(adapter, reg->cmdrsp_addr_hi,
				      (u32)((u64)cmdrsp_buf_pa >> 32))) {
			mwifiex_dbg(adapter, ERROR,
				    "Failed to write download cmd to boot code.\n");
			ret = -1;
			goto done;
		}
	}

	cmd_buf_pa = MWIFIEX_SKB_DMA_ADDR(card->cmd_buf);

	if (mwifiex_write_reg(adapter, reg->cmd_addr_lo,
			      (u32)cmd_buf_pa)) {
		mwifiex_dbg(adapter, ERROR,
			    "Failed to write download cmd to boot code.\n");
		ret = -1;
		goto done;
	}

	if (mwifiex_write_reg(adapter, reg->cmd_addr_hi,
			      (u32)((u64)cmd_buf_pa >> 32))) {
		mwifiex_dbg(adapter, ERROR,
			    "Failed to write download cmd to boot code.\n");
		ret = -1;
		goto done;
	}


	if (mwifiex_write_reg(adapter, reg->cmd_size,
			      card->cmd_buf->len)) {
		mwifiex_dbg(adapter, ERROR,
			    "Failed to write cmd len to reg->cmd_size\n");
		ret = -1;
		goto done;
	}


	if (mwifiex_write_reg(adapter, PCIE_CPU_INT_EVENT,
			      CPU_INTR_DOOR_BELL)) {
		mwifiex_dbg(adapter, ERROR,
			    "Failed to assert door-bell intr\n");
		ret = -1;
		goto done;
	}

done:
	if (ret)
		adapter->cmd_sent = false;

	return 0;
}
