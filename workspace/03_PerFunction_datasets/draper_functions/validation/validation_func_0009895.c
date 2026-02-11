wlc_phy_txpower_ipa_upd(struct brcms_phy *pi)
{

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		pi->ipa2g_on = (pi->srom_fem2g.extpagain == 2);
		pi->ipa5g_on = (pi->srom_fem5g.extpagain == 2);
	} else {
		pi->ipa2g_on = false;
		pi->ipa5g_on = false;
	}
}
