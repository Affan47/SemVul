void rtl8xxxu_power_off(struct rtl8xxxu_priv *priv)
{
	u8 val8;
	u16 val16;
	u32 val32;


	if (priv->rtl_chip == RTL8188R) {
		val32 = rtl8xxxu_read32(priv, REG_FPGA0_XCD_RF_PARM);
		val32 |= BIT(1);
		rtl8xxxu_write32(priv, REG_FPGA0_XCD_RF_PARM, val32);
	}

	rtl8xxxu_flush_fifo(priv);

	rtl8xxxu_active_to_lps(priv);


	rtl8xxxu_write8(priv, REG_RF_CTRL, 0x00);


	if (rtl8xxxu_read8(priv, REG_MCU_FW_DL) & MCU_FW_RAM_SEL)
		rtl8xxxu_firmware_self_reset(priv);


	val16 = rtl8xxxu_read16(priv, REG_SYS_FUNC);
	val16 &= ~SYS_FUNC_CPU_ENABLE;
	rtl8xxxu_write16(priv, REG_SYS_FUNC, val16);


	rtl8xxxu_write8(priv, REG_MCU_FW_DL, 0x00);

	rtl8xxxu_active_to_emu(priv);
	rtl8xxxu_emu_to_disabled(priv);


	val8 = rtl8xxxu_read8(priv, REG_RSV_CTRL + 1);
	val8 &= ~BIT(0);
	rtl8xxxu_write8(priv, REG_RSV_CTRL + 1, val8);

	val8 = rtl8xxxu_read8(priv, REG_RSV_CTRL + 1);
	val8 |= BIT(0);
	rtl8xxxu_write8(priv, REG_RSV_CTRL + 1, val8);


	rtl8xxxu_write8(priv, REG_RSV_CTRL, 0x0e);
}
