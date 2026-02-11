wlc_phy_ant_rxdiv_set(struct brcms_phy_pub *ppi, u8 val)
{
	struct brcms_phy *pi = container_of(ppi, struct brcms_phy, pubpi_ro);
	bool suspend;

	pi->sh->rx_antdiv = val;

	if (!(ISNPHY(pi) && D11REV_IS(pi->sh->corerev, 16))) {
		if (val > ANT_RX_DIV_FORCE_1)
			wlapi_bmac_mhf(pi->sh->physhim, MHF1, MHF1_ANTDIV,
				       MHF1_ANTDIV, BRCM_BAND_ALL);
		else
			wlapi_bmac_mhf(pi->sh->physhim, MHF1, MHF1_ANTDIV, 0,
				       BRCM_BAND_ALL);
	}

	if (ISNPHY(pi))
		return;

	if (!pi->sh->clk)
		return;

	suspend = (0 == (bcma_read32(pi->d11core, D11REGOFFS(maccontrol)) &
			 MCTL_EN_MAC));
	if (!suspend)
		wlapi_suspend_mac_and_wait(pi->sh->physhim);

	if (ISLCNPHY(pi)) {
		if (val > ANT_RX_DIV_FORCE_1) {
			mod_phy_reg(pi, 0x410, (0x1 << 1), 0x01 << 1);
			mod_phy_reg(pi, 0x410,
				    (0x1 << 0),
				    ((ANT_RX_DIV_START_1 == val) ? 1 : 0) << 0);
		} else {
			mod_phy_reg(pi, 0x410, (0x1 << 1), 0x00 << 1);
			mod_phy_reg(pi, 0x410, (0x1 << 0), (u16) val << 0);
		}
	}

	if (!suspend)
		wlapi_enable_mac(pi->sh->physhim);

	return;
}
