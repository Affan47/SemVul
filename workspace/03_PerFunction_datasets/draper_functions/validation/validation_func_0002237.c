sky2_mac_intr(struct sky2_hw *hw, unsigned port)
{
	struct net_device *dev = hw->dev[port];
	u8 status = sky2_read8(hw, SK_REG(port, GMAC_IRQ_SRC));

	DBGIO(PFX "%s: mac interrupt status 0x%x\n", dev->name, status);

	if (status & GM_IS_RX_CO_OV)
		gma_read16(hw, port, GM_RX_IRQ_SRC);

	if (status & GM_IS_TX_CO_OV)
		gma_read16(hw, port, GM_TX_IRQ_SRC);

	if (status & GM_IS_RX_FF_OR) {
		sky2_write8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_CLI_RX_FO);
	}

	if (status & GM_IS_TX_FF_UR) {
		sky2_write8(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_CLI_TX_FU);
	}
}
