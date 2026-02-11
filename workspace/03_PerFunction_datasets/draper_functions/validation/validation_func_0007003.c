b44_phy_reset(struct b44 *bp)
{
	u32 val;
	int err;

	if (bp->flags & B44_FLAG_EXTERNAL_PHY)
		return 0;
	err = b44_writephy(bp, MII_BMCR, BMCR_RESET);
	if (err)
		return err;
	udelay(100);
	err = b44_readphy(bp, MII_BMCR, &val);
	if (!err) {
		if (val & BMCR_RESET) {
			netdev_err(bp->dev, "PHY Reset would not complete\n");
			err = -ENODEV;
		}
	}

	return err;
}
