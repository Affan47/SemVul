wlc_phy_set_rssi_2055_vcm(struct brcms_phy *pi, u8 rssi_type, u8 *vcm_buf)
{
	u8 core;

	for (core = 0; core < pi->pubpi.phy_corenum; core++) {
		if (rssi_type == NPHY_RSSI_SEL_NB) {
			if (core == PHY_CORE_0) {
				mod_radio_reg(pi,
					      RADIO_2055_CORE1_B0_NBRSSI_VCM,
					      RADIO_2055_NBRSSI_VCM_I_MASK,
					      vcm_buf[2 *
						      core] <<
					      RADIO_2055_NBRSSI_VCM_I_SHIFT);
				mod_radio_reg(pi,
					      RADIO_2055_CORE1_RXBB_RSSI_CTRL5,
					      RADIO_2055_NBRSSI_VCM_Q_MASK,
					      vcm_buf[2 * core +
						      1] <<
					      RADIO_2055_NBRSSI_VCM_Q_SHIFT);
			} else {
				mod_radio_reg(pi,
					      RADIO_2055_CORE2_B0_NBRSSI_VCM,
					      RADIO_2055_NBRSSI_VCM_I_MASK,
					      vcm_buf[2 *
						      core] <<
					      RADIO_2055_NBRSSI_VCM_I_SHIFT);
				mod_radio_reg(pi,
					      RADIO_2055_CORE2_RXBB_RSSI_CTRL5,
					      RADIO_2055_NBRSSI_VCM_Q_MASK,
					      vcm_buf[2 * core +
						      1] <<
					      RADIO_2055_NBRSSI_VCM_Q_SHIFT);
			}
		} else {
			if (core == PHY_CORE_0)
				mod_radio_reg(pi,
					      RADIO_2055_CORE1_RXBB_RSSI_CTRL5,
					      RADIO_2055_WBRSSI_VCM_IQ_MASK,
					      vcm_buf[2 *
						      core] <<
					      RADIO_2055_WBRSSI_VCM_IQ_SHIFT);
			else
				mod_radio_reg(pi,
					      RADIO_2055_CORE2_RXBB_RSSI_CTRL5,
					      RADIO_2055_WBRSSI_VCM_IQ_MASK,
					      vcm_buf[2 *
						      core] <<
					      RADIO_2055_WBRSSI_VCM_IQ_SHIFT);
		}
	}
}
