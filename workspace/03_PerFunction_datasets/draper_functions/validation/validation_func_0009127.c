pch_gbe_mac_set_wol_event(struct pch_gbe_hw *hw, u32 wu_evt)
{
	struct pch_gbe_adapter *adapter = pch_gbe_hw_to_adapter(hw);
	u32 addr_mask;

	netdev_dbg(adapter->netdev, "wu_evt : 0x%08x  ADDR_MASK reg : 0x%08x\n",
		   wu_evt, ioread32(&hw->reg->ADDR_MASK));

	if (wu_evt) {

		addr_mask = ioread32(&hw->reg->ADDR_MASK);
		iowrite32(addr_mask, &hw->reg->WOL_ADDR_MASK);

		pch_gbe_wait_clr_bit(&hw->reg->WOL_ADDR_MASK, PCH_GBE_WLA_BUSY);
		iowrite32(0, &hw->reg->WOL_ST);
		iowrite32((wu_evt | PCH_GBE_WLC_WOL_MODE), &hw->reg->WOL_CTRL);
		iowrite32(0x02, &hw->reg->TCPIP_ACC);
		iowrite32(PCH_GBE_INT_ENABLE_MASK, &hw->reg->INT_EN);
	} else {
		iowrite32(0, &hw->reg->WOL_CTRL);
		iowrite32(0, &hw->reg->WOL_ST);
	}
	return;
}
