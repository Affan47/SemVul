void rtl8xxxu_gen1_init_aggregation(struct rtl8xxxu_priv *priv)
{
	u8 agg_ctrl, usb_spec, page_thresh, timeout;

	usb_spec = rtl8xxxu_read8(priv, REG_USB_SPECIAL_OPTION);
	usb_spec &= ~USB_SPEC_USB_AGG_ENABLE;
	rtl8xxxu_write8(priv, REG_USB_SPECIAL_OPTION, usb_spec);

	agg_ctrl = rtl8xxxu_read8(priv, REG_TRXDMA_CTRL);
	agg_ctrl &= ~TRXDMA_CTRL_RXDMA_AGG_EN;

	if (!rtl8xxxu_dma_aggregation) {
		rtl8xxxu_write8(priv, REG_TRXDMA_CTRL, agg_ctrl);
		return;
	}

	agg_ctrl |= TRXDMA_CTRL_RXDMA_AGG_EN;
	rtl8xxxu_write8(priv, REG_TRXDMA_CTRL, agg_ctrl);


	page_thresh = (priv->fops->rx_agg_buf_size / 512);
	if (rtl8xxxu_dma_agg_pages >= 0) {
		if (rtl8xxxu_dma_agg_pages <= page_thresh)
			timeout = page_thresh;
		else if (rtl8xxxu_dma_agg_pages <= 6)
			dev_err(&priv->udev->dev,
				"%s: dma_agg_pages=%i too small, minimum is 6\n",
				__func__, rtl8xxxu_dma_agg_pages);
		else
			dev_err(&priv->udev->dev,
				"%s: dma_agg_pages=%i larger than limit %i\n",
				__func__, rtl8xxxu_dma_agg_pages, page_thresh);
	}
	rtl8xxxu_write8(priv, REG_RXDMA_AGG_PG_TH, page_thresh);


	timeout = 4;

	if (rtl8xxxu_dma_agg_timeout >= 0) {
		if (rtl8xxxu_dma_agg_timeout <= 127)
			timeout = rtl8xxxu_dma_agg_timeout;
		else
			dev_err(&priv->udev->dev,
				"%s: Invalid dma_agg_timeout: %i\n",
				__func__, rtl8xxxu_dma_agg_timeout);
	}

	rtl8xxxu_write8(priv, REG_RXDMA_AGG_PG_TH + 1, timeout);
	rtl8xxxu_write8(priv, REG_USB_DMA_AGG_TO, timeout);
	priv->rx_buf_aggregation = 1;
}
