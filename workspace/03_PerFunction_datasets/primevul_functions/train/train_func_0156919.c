void rtl8xxxu_disabled_to_emu(struct rtl8xxxu_priv *priv)
{
	u8 val8;


	val8 = rtl8xxxu_read8(priv, REG_APS_FSMCO + 1);
	val8 &= ~(BIT(3) | BIT(7));
	rtl8xxxu_write8(priv, REG_APS_FSMCO + 1, val8);


	val8 = rtl8xxxu_read8(priv, REG_GPIO_INTM + 2);
	val8 &= ~BIT(0);
	rtl8xxxu_write8(priv, REG_GPIO_INTM + 2, val8);


	val8 = rtl8xxxu_read8(priv, REG_APS_FSMCO + 1);
	val8 &= ~(BIT(3) | BIT(4));
	rtl8xxxu_write8(priv, REG_APS_FSMCO + 1, val8);
}
