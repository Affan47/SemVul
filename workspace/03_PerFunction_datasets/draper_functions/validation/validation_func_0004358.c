enable_status_frames(struct phy_device *phydev, bool on)
{
	struct dp83640_private *dp83640 = phydev->priv;
	struct dp83640_clock *clock = dp83640->clock;
	u16 cfg0 = 0, ver;

	if (on)
		cfg0 = PSF_EVNT_EN | PSF_RXTS_EN | PSF_TXTS_EN | ENDIAN_FLAG;

	ver = (PSF_PTPVER & VERSIONPTP_MASK) << VERSIONPTP_SHIFT;

	mutex_lock(&clock->extreg_lock);

	ext_write(0, phydev, PAGE5, PSF_CFG0, cfg0);
	ext_write(0, phydev, PAGE6, PSF_CFG1, ver);

	mutex_unlock(&clock->extreg_lock);

	if (!phydev->attached_dev) {
		pr_warn("expected to find an attached netdevice\n");
		return;
	}

	if (on) {
		if (dev_mc_add(phydev->attached_dev, status_frame_dst))
			pr_warn("failed to add mc address\n");
	} else {
		if (dev_mc_del(phydev->attached_dev, status_frame_dst))
			pr_warn("failed to delete mc address\n");
	}
}
