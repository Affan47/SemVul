islpci_free_memory(islpci_private *priv)
{
	int counter;

	if (priv->device_base)
		iounmap(priv->device_base);
	priv->device_base = NULL;


	if (priv->driver_mem_address)
		pci_free_consistent(priv->pdev, HOST_MEM_BLOCK,
				    priv->driver_mem_address,
				    priv->device_host_address);


	priv->driver_mem_address = NULL;
	priv->device_host_address = 0;
	priv->device_psm_buffer = 0;
	priv->control_block = NULL;


        for (counter = 0; counter < ISL38XX_CB_MGMT_QSIZE; counter++) {
		struct islpci_membuf *buf = &priv->mgmt_rx[counter];
		if (buf->pci_addr)
			pci_unmap_single(priv->pdev, buf->pci_addr,
					 buf->size, PCI_DMA_FROMDEVICE);
		buf->pci_addr = 0;
		kfree(buf->mem);
		buf->size = 0;
		buf->mem = NULL;
        }


	for (counter = 0; counter < ISL38XX_CB_RX_QSIZE; counter++) {
		if (priv->pci_map_rx_address[counter])
			pci_unmap_single(priv->pdev,
					 priv->pci_map_rx_address[counter],
					 MAX_FRAGMENT_SIZE_RX + 2,
					 PCI_DMA_FROMDEVICE);
		priv->pci_map_rx_address[counter] = 0;

		if (priv->data_low_rx[counter])
			dev_kfree_skb(priv->data_low_rx[counter]);
		priv->data_low_rx[counter] = NULL;
	}


	prism54_acl_clean(&priv->acl);
	prism54_wpa_bss_ie_clean(priv);
	mgt_clean(priv);

	return 0;
}
