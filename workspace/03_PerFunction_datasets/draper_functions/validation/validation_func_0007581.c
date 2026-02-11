vsc82xx_config_intr(struct phy_device *phydev)
{
	int err;

	if (phydev->interrupts == PHY_INTERRUPT_ENABLED)
		err = phy_write(phydev, MII_VSC8244_IMASK,
			(phydev->drv->phy_id == PHY_ID_VSC8234 ||
			 phydev->drv->phy_id == PHY_ID_VSC8244 ||
			 phydev->drv->phy_id == PHY_ID_VSC8514 ||
			 phydev->drv->phy_id == PHY_ID_VSC8574 ||
			 phydev->drv->phy_id == PHY_ID_VSC8601) ?
				MII_VSC8244_IMASK_MASK :
				MII_VSC8221_IMASK_MASK);
	else {


		err = phy_read(phydev, MII_VSC8244_ISTAT);

		if (err < 0)
			return err;

		err = phy_write(phydev, MII_VSC8244_IMASK, 0);
	}

	return err;
}
