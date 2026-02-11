bnx2x_power_sfp_module(struct link_params *params,
				   struct bnx2x_phy *phy,
				   u8 power)
{
	struct bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "Setting SFP+ power to %x\n", power);

	switch (phy->type) {
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727:
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722:
		bnx2x_8727_power_module(params->bp, phy, power);
		break;
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT:
		bnx2x_warpcore_power_module(params, power);
		break;
	default:
		break;
	}
}
