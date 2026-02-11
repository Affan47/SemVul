igb_rx_fifo_flush_82575(struct e1000_hw *hw)
{
	u32 rctl, rlpml, rxdctl[4], rfctl, temp_rctl, rx_enabled;
	int i, ms_wait;

	DEBUGFUNC("igb_rx_fifo_workaround_82575");
	if (hw->mac.type != e1000_82575 ||
	    !(E1000_READ_REG(hw, E1000_MANC) & E1000_MANC_RCV_TCO_EN))
		return;


	for (i = 0; i < 4; i++) {
		rxdctl[i] = E1000_READ_REG(hw, E1000_RXDCTL(i));
		E1000_WRITE_REG(hw, E1000_RXDCTL(i),
		                rxdctl[i] & ~E1000_RXDCTL_QUEUE_ENABLE);
	}

	for (ms_wait = 0; ms_wait < 10; ms_wait++) {
		msec_delay(1);
		rx_enabled = 0;
		for (i = 0; i < 4; i++)
			rx_enabled |= E1000_READ_REG(hw, E1000_RXDCTL(i));
		if (!(rx_enabled & E1000_RXDCTL_QUEUE_ENABLE))
			break;
	}

	if (ms_wait == 10) {
		DEBUGOUT("Queue disable timed out after 10ms\n");
        }


	rfctl = E1000_READ_REG(hw, E1000_RFCTL);
	E1000_WRITE_REG(hw, E1000_RFCTL, rfctl & ~E1000_RFCTL_LEF);

	rlpml = E1000_READ_REG(hw, E1000_RLPML);
	E1000_WRITE_REG(hw, E1000_RLPML, 0);

	rctl = E1000_READ_REG(hw, E1000_RCTL);
	temp_rctl = rctl & ~(E1000_RCTL_EN | E1000_RCTL_SBP);
	temp_rctl |= E1000_RCTL_LPE;

	E1000_WRITE_REG(hw, E1000_RCTL, temp_rctl);
	E1000_WRITE_REG(hw, E1000_RCTL, temp_rctl | E1000_RCTL_EN);
	E1000_WRITE_FLUSH(hw);
	msec_delay(2);


	for (i = 0; i < 4; i++)
		E1000_WRITE_REG(hw, E1000_RXDCTL(i), rxdctl[i]);
	E1000_WRITE_REG(hw, E1000_RCTL, rctl);
	E1000_WRITE_FLUSH(hw);

	E1000_WRITE_REG(hw, E1000_RLPML, rlpml);
	E1000_WRITE_REG(hw, E1000_RFCTL, rfctl);


	E1000_READ_REG(hw, E1000_ROC);
	E1000_READ_REG(hw, E1000_RNBC);
	E1000_READ_REG(hw, E1000_MPC);
}
