ixgbe_setup_mtqc(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 rttdcs, mtqc;
	u8 tcs = netdev_get_num_tc(adapter->netdev);

	if (hw->mac.type == ixgbe_mac_82598EB)
		return;


	rttdcs = IXGBE_READ_REG(hw, IXGBE_RTTDCS);
	rttdcs |= IXGBE_RTTDCS_ARBDIS;
	IXGBE_WRITE_REG(hw, IXGBE_RTTDCS, rttdcs);


	if (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) {
		mtqc = IXGBE_MTQC_VT_ENA;
		if (tcs > 4)
			mtqc |= IXGBE_MTQC_RT_ENA | IXGBE_MTQC_8TC_8TQ;
		else if (tcs > 1)
			mtqc |= IXGBE_MTQC_RT_ENA | IXGBE_MTQC_4TC_4TQ;
		else if (adapter->ring_feature[RING_F_RSS].indices == 4)
			mtqc |= IXGBE_MTQC_32VF;
		else
			mtqc |= IXGBE_MTQC_64VF;
	} else {
		if (tcs > 4)
			mtqc = IXGBE_MTQC_RT_ENA | IXGBE_MTQC_8TC_8TQ;
		else if (tcs > 1)
			mtqc = IXGBE_MTQC_RT_ENA | IXGBE_MTQC_4TC_4TQ;
		else
			mtqc = IXGBE_MTQC_64Q_1PB;
	}

	IXGBE_WRITE_REG(hw, IXGBE_MTQC, mtqc);


	if (tcs) {
		u32 sectx = IXGBE_READ_REG(hw, IXGBE_SECTXMINIFG);
		sectx |= IXGBE_SECTX_DCB;
		IXGBE_WRITE_REG(hw, IXGBE_SECTXMINIFG, sectx);
	}


	rttdcs &= ~IXGBE_RTTDCS_ARBDIS;
	IXGBE_WRITE_REG(hw, IXGBE_RTTDCS, rttdcs);
}
