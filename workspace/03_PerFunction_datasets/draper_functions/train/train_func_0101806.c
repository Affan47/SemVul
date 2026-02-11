b43_nphy_update_tx_cal_ladder(struct b43_wldev *dev, u16 core)
{
	struct b43_phy_n *nphy = dev->phy.n;
	int i;
	u16 scale, entry;

	u16 tmp = nphy->txcal_bbmult;
	if (core == 0)
		tmp >>= 8;
	tmp &= 0xff;

	for (i = 0; i < 18; i++) {
		scale = (ladder_lo[i].percent * tmp) / 100;
		entry = ((scale & 0xFF) << 8) | ladder_lo[i].g_env;
		b43_ntab_write(dev, B43_NTAB16(15, i), entry);

		scale = (ladder_iq[i].percent * tmp) / 100;
		entry = ((scale & 0xFF) << 8) | ladder_iq[i].g_env;
		b43_ntab_write(dev, B43_NTAB16(15, i + 32), entry);
	}
}
