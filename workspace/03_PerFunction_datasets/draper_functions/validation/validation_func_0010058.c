jme_wait_link(struct jme_adapter *jme)
{
	u32 phylink, to = JME_WAIT_LINK_TIME;

	mdelay(1000);
	phylink = jme_linkstat_from_phy(jme);
	while (!(phylink & PHY_LINK_UP) && (to -= 10) > 0) {
		mdelay(10);
		phylink = jme_linkstat_from_phy(jme);
	}
}
