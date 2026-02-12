static void rtl8723a_phy_lc_calibrate(struct rtl8xxxu_priv *priv)
{
	u32 val32;
	u32 rf_amode, rf_bmode = 0, lstf;


	lstf = rtl8xxxu_read32(priv, REG_OFDM1_LSTF);

	if (lstf & OFDM_LSTF_MASK) {

		val32 = lstf & ~OFDM_LSTF_MASK;
		rtl8xxxu_write32(priv, REG_OFDM1_LSTF, val32);


		rf_amode = rtl8xxxu_read_rfreg(priv, RF_A, RF6052_REG_AC);


		rtl8xxxu_write_rfreg(priv, RF_A, RF6052_REG_AC,
				     (rf_amode & 0x8ffff) | 0x10000);


		if (priv->tx_paths > 1) {
			rf_bmode = rtl8xxxu_read_rfreg(priv, RF_B,
						       RF6052_REG_AC);

			rtl8xxxu_write_rfreg(priv, RF_B, RF6052_REG_AC,
					     (rf_bmode & 0x8ffff) | 0x10000);
		}
	} else {


		rtl8xxxu_write8(priv, REG_TXPAUSE, 0xff);
	}


	if (priv->fops->has_s0s1)
		rtl8xxxu_write_rfreg(priv, RF_A, RF6052_REG_S0S1, 0xdfbe0);
	val32 = rtl8xxxu_read_rfreg(priv, RF_A, RF6052_REG_MODE_AG);
	val32 |= 0x08000;
	rtl8xxxu_write_rfreg(priv, RF_A, RF6052_REG_MODE_AG, val32);

	msleep(100);

	if (priv->fops->has_s0s1)
		rtl8xxxu_write_rfreg(priv, RF_A, RF6052_REG_S0S1, 0xdffe0);


	if (lstf & OFDM_LSTF_MASK) {

		rtl8xxxu_write32(priv, REG_OFDM1_LSTF, lstf);
		rtl8xxxu_write_rfreg(priv, RF_A, RF6052_REG_AC, rf_amode);


		if (priv->tx_paths > 1)
			rtl8xxxu_write_rfreg(priv, RF_B, RF6052_REG_AC,
					     rf_bmode);
	} else
		rtl8xxxu_write8(priv, REG_TXPAUSE, 0x00);
}
