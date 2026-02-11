dm_restorepowerindex(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8	index;

	for (index = 0; index < 6; index++)
		rtl_write_byte(rtlpriv, power_index_reg[index],
			       rtlpriv->dm.powerindex_backup[index]);
}
