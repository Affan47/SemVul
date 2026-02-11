mt7601u_phy_rf_pa_mode_val(struct mt7601u_dev *dev, int phy_mode, int tx_rate)
{
	static const s16 decode_tb[] = { 0, 8847, -5734, -5734 };
	u32 reg;

	switch (phy_mode) {
	case MT_PHY_TYPE_OFDM:
		tx_rate += 4;
	case MT_PHY_TYPE_CCK:
		reg = dev->rf_pa_mode[0];
		break;
	default:
		reg = dev->rf_pa_mode[1];
		break;
	}

	return decode_tb[(reg >> (tx_rate * 2)) & 0x3];
}
