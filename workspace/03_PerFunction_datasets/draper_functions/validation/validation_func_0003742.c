b43_nphy_tx_tone(struct b43_wldev *dev, u32 freq, u16 max_val,
			    bool iqmode, bool dac_test, bool modify_bbmult)
{
	u16 samp = b43_nphy_gen_load_samples(dev, freq, max_val, dac_test);
	if (samp == 0)
		return -1;
	b43_nphy_run_samples(dev, samp, 0xFFFF, 0, iqmode, dac_test,
			     modify_bbmult);
	return 0;
}
