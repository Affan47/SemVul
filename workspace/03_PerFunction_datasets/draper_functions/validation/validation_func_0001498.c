rtl92s_phy_query_bb_reg(struct ieee80211_hw *hw, u32 regaddr, u32 bitmask)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 returnvalue = 0, originalvalue, bitshift;

	RT_TRACE(rtlpriv, COMP_RF, DBG_TRACE, "regaddr(%#x), bitmask(%#x)\n",
		 regaddr, bitmask);

	originalvalue = rtl_read_dword(rtlpriv, regaddr);
	bitshift = _rtl92s_phy_calculate_bit_shift(bitmask);
	returnvalue = (originalvalue & bitmask) >> bitshift;

	RT_TRACE(rtlpriv, COMP_RF, DBG_TRACE, "BBR MASK=0x%x Addr[0x%x]=0x%x\n",
		 bitmask, regaddr, originalvalue);

	return returnvalue;

}
