stmmac_refill_desc3(void *priv_ptr, struct dma_desc *p)
{
	struct stmmac_priv *priv = (struct stmmac_priv *)priv_ptr;

	if (priv->hwts_rx_en && !priv->extend_desc)


		p->des3 = (unsigned int)(priv->dma_rx_phy +
					 (((priv->dirty_rx) + 1) %
					  priv->dma_rx_size) *
					 sizeof(struct dma_desc));
}
