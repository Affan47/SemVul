capture_restore(struct rcar_vin_priv *priv, u32 vnmc)
{
	unsigned long timeout = jiffies + 10 * HZ;


	while ((ioread32(priv->base + VNMS_REG) & VNMS_AV) &&
		time_before(jiffies, timeout))
		msleep(1);

	if (time_after(jiffies, timeout)) {
		dev_err(priv->ici.v4l2_dev.dev,
			"Timeout waiting for frame end! Interface problem?\n");
		return;
	}

	iowrite32(vnmc, priv->base + VNMC_REG);
}
