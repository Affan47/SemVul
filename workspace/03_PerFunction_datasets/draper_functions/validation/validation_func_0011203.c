spdif_irq_dpll_lock(struct fsl_spdif_priv *spdif_priv)
{
	struct regmap *regmap = spdif_priv->regmap;
	struct platform_device *pdev = spdif_priv->pdev;
	u32 locked;

	regmap_read(regmap, REG_SPDIF_SRPC, &locked);
	locked &= SRPC_DPLL_LOCKED;

	dev_dbg(&pdev->dev, "isr: Rx dpll %s \n",
			locked ? "locked" : "loss lock");

	spdif_priv->dpll_locked = locked ? true : false;
}
