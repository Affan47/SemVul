phy_resume(struct phy_device *phydev)
{
	struct phy_driver *phydrv = to_phy_driver(phydev->dev.driver);
	int ret = 0;

	if (phydrv->resume)
		ret = phydrv->resume(phydev);

	if (ret)
		return ret;

	phydev->suspended = false;

	return ret;
}
