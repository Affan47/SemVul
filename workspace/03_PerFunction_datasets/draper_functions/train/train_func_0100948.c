gem_init_phy(struct gem *gp)
{
	u32 mifcfg;


	mifcfg = readl(gp->regs + MIF_CFG);
	mifcfg &= ~MIF_CFG_BBMODE;
	writel(mifcfg, gp->regs + MIF_CFG);

	if (gp->pdev->vendor == PCI_VENDOR_ID_APPLE) {
		int i;


		for (i = 0; i < 3; i++) {
#ifdef CONFIG_PPC_PMAC
			pmac_call_feature(PMAC_FTR_GMAC_PHY_RESET, gp->of_node, 0, 0);
			msleep(20);
#endif


			sungem_phy_write(gp, MII_BMCR, BMCR_RESET);
			msleep(20);
			if (sungem_phy_read(gp, MII_BMCR) != 0xffff)
				break;
			if (i == 2)
				netdev_warn(gp->dev, "GMAC PHY not responding !\n");
		}
	}

	if (gp->pdev->vendor == PCI_VENDOR_ID_SUN &&
	    gp->pdev->device == PCI_DEVICE_ID_SUN_GEM) {
		u32 val;


		if (gp->phy_type == phy_mii_mdio0 ||
		    gp->phy_type == phy_mii_mdio1) {
			val = PCS_DMODE_MGM;
		} else if (gp->phy_type == phy_serialink) {
			val = PCS_DMODE_SM | PCS_DMODE_GMOE;
		} else {
			val = PCS_DMODE_ESM;
		}

		writel(val, gp->regs + PCS_DMODE);
	}

	if (gp->phy_type == phy_mii_mdio0 ||
	    gp->phy_type == phy_mii_mdio1) {

		sungem_phy_probe(&gp->phy_mii, gp->mii_phy_addr);


		if (gp->phy_mii.def && gp->phy_mii.def->ops->init)
			gp->phy_mii.def->ops->init(&gp->phy_mii);
	} else {
		gem_pcs_reset(gp);
		gem_pcs_reinit_adv(gp);
	}


	gp->timer_ticks = 0;
	gp->lstate = link_down;
	netif_carrier_off(gp->dev);


	if (gp->phy_type == phy_mii_mdio0 ||
	    gp->phy_type == phy_mii_mdio1)
		netdev_info(gp->dev, "Found %s PHY\n",
			    gp->phy_mii.def ? gp->phy_mii.def->name : "no");

	gem_begin_auto_negotiation(gp, NULL);
}
