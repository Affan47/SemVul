mpt_lan_send_reply(struct net_device *dev, LANSendReply_t *pSendRep)
{
	struct mpt_lan_priv *priv = netdev_priv(dev);
	MPT_ADAPTER *mpt_dev = priv->mpt_dev;
	struct sk_buff *sent;
	unsigned long flags;
	int FreeReqFrame = 0;
	u32 *pContext;
	u32 ctx;
	u8 count;

	count = pSendRep->NumberOfContexts;

	dioprintk((KERN_INFO MYNAM ": send_reply: IOCStatus: %04x\n",
		 le16_to_cpu(pSendRep->IOCStatus)));


	switch (le16_to_cpu(pSendRep->IOCStatus) & MPI_IOCSTATUS_MASK) {
	case MPI_IOCSTATUS_SUCCESS:
		dev->stats.tx_packets += count;
		break;

	case MPI_IOCSTATUS_LAN_CANCELED:
	case MPI_IOCSTATUS_LAN_TRANSMIT_ABORTED:
		break;

	case MPI_IOCSTATUS_INVALID_SGL:
		dev->stats.tx_errors += count;
		printk (KERN_ERR MYNAM ": %s/%s: ERROR - Invalid SGL sent to IOC!\n",
				IOC_AND_NETDEV_NAMES_s_s(dev));
		goto out;

	default:
		dev->stats.tx_errors += count;
		break;
	}

	pContext = &pSendRep->BufferContext;

	spin_lock_irqsave(&priv->txfidx_lock, flags);
	while (count > 0) {
		ctx = GET_LAN_BUFFER_CONTEXT(le32_to_cpu(*pContext));

		sent = priv->SendCtl[ctx].skb;
		dev->stats.tx_bytes += sent->len;

		dioprintk((KERN_INFO MYNAM ": %s/%s: @%s, skb %p sent.\n",
				IOC_AND_NETDEV_NAMES_s_s(dev),
				__func__, sent));

		priv->SendCtl[ctx].skb = NULL;
		pci_unmap_single(mpt_dev->pcidev, priv->SendCtl[ctx].dma,
				 priv->SendCtl[ctx].len, PCI_DMA_TODEVICE);
		dev_kfree_skb_irq(sent);

		priv->mpt_txfidx[++priv->mpt_txfidx_tail] = ctx;

		pContext++;
		count--;
	}
	spin_unlock_irqrestore(&priv->txfidx_lock, flags);

out:
	if (!(pSendRep->MsgFlags & MPI_MSGFLAGS_CONTINUATION_REPLY))
		FreeReqFrame = 1;

	netif_wake_queue(dev);
	return FreeReqFrame;
}
