rtl_speed_down(struct rtl8169_private *tp)
{
	u32 adv;
	int lpa;

	rtl_writephy(tp, 0x1f, 0x0000);
	lpa = rtl_readphy(tp, MII_LPA);

	if (lpa & (LPA_10HALF | LPA_10FULL))
		adv = ADVERTISED_10baseT_Half | ADVERTISED_10baseT_Full;
	else if (lpa & (LPA_100HALF | LPA_100FULL))
		adv = ADVERTISED_10baseT_Half | ADVERTISED_10baseT_Full |
		      ADVERTISED_100baseT_Half | ADVERTISED_100baseT_Full;
	else
		adv = ADVERTISED_10baseT_Half | ADVERTISED_10baseT_Full |
		      ADVERTISED_100baseT_Half | ADVERTISED_100baseT_Full |
		      (tp->mii.supports_gmii ?
		       ADVERTISED_1000baseT_Half |
		       ADVERTISED_1000baseT_Full : 0);

	rtl8169_set_speed(tp->dev, AUTONEG_ENABLE, SPEED_1000, DUPLEX_FULL,
			  adv);
}
