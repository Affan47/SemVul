static int rtl8xxxu_active_to_emu(struct rtl8xxxu_priv *priv)
{
	u8 val8;
	int count, ret = 0;


	rtl8xxxu_write8(priv, REG_RF_CTRL, 0);


	val8 = rtl8xxxu_read8(priv, REG_LEDCFG2);
	val8 &= ~LEDCFG2_DPDT_SELECT;
	rtl8xxxu_write8(priv, REG_LEDCFG2, val8);


	val8 = rtl8xxxu_read8(priv, REG_APS_FSMCO + 1);
	val8 |= BIT(1);
	rtl8xxxu_write8(priv, REG_APS_FSMCO + 1, val8);

	for (count = RTL8XXXU_MAX_REG_POLL; count; count--) {
		val8 = rtl8xxxu_read8(priv, REG_APS_FSMCO + 1);
		if ((val8 & BIT(1)) == 0)
			break;
		udelay(10);
	}

	if (!count) {
		dev_warn(&priv->udev->dev, "%s: Disabling MAC timed out\n",
			 __func__);
		ret = -EBUSY;
		goto exit;
	}


	val8 = rtl8xxxu_read8(priv, REG_SYS_ISO_CTRL);
	val8 |= SYS_ISO_ANALOG_IPS;
	rtl8xxxu_write8(priv, REG_SYS_ISO_CTRL, val8);


	val8 = rtl8xxxu_read8(priv, REG_LDOA15_CTRL);
	val8 &= ~LDOA15_ENABLE;
	rtl8xxxu_write8(priv, REG_LDOA15_CTRL, val8);

exit:
	return ret;
}
