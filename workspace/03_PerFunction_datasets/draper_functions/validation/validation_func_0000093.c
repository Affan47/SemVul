_rtl92de_efuse_update_chip_version(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	enum version_8192d chipver = rtlpriv->rtlhal.version;
	u8 cutvalue[2];
	u16 chipvalue;

	rtlpriv->intf_ops->read_efuse_byte(hw, EEPROME_CHIP_VERSION_H,
					   &cutvalue[1]);
	rtlpriv->intf_ops->read_efuse_byte(hw, EEPROME_CHIP_VERSION_L,
					   &cutvalue[0]);
	chipvalue = (cutvalue[1] << 8) | cutvalue[0];
	switch (chipvalue) {
	case 0xAA55:
		chipver |= CHIP_92D_C_CUT;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "C-CUT!!!\n");
		break;
	case 0x9966:
		chipver |= CHIP_92D_D_CUT;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "D-CUT!!!\n");
		break;
	case 0xCC33:
		chipver |= CHIP_92D_E_CUT;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "E-CUT!!!\n");
		break;
	default:
		chipver |= CHIP_92D_D_CUT;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_EMERG, "Unknown CUT!\n");
		break;
	}
	rtlpriv->rtlhal.version = chipver;
}
