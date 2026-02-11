igbvf_assign_vector(struct igbvf_adapter *adapter, int rx_queue,
				int tx_queue, int msix_vector)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 ivar, index;


	if (rx_queue > IGBVF_NO_QUEUE) {
		index = (rx_queue >> 1);
		ivar = array_er32(IVAR0, index);
		if (rx_queue & 0x1) {

			ivar = ivar & 0xFF00FFFF;
			ivar |= (msix_vector | E1000_IVAR_VALID) << 16;
		} else {

			ivar = ivar & 0xFFFFFF00;
			ivar |= msix_vector | E1000_IVAR_VALID;
		}
		adapter->rx_ring[rx_queue].eims_value = 1 << msix_vector;
		array_ew32(IVAR0, index, ivar);
	}
	if (tx_queue > IGBVF_NO_QUEUE) {
		index = (tx_queue >> 1);
		ivar = array_er32(IVAR0, index);
		if (tx_queue & 0x1) {

			ivar = ivar & 0x00FFFFFF;
			ivar |= (msix_vector | E1000_IVAR_VALID) << 24;
		} else {

			ivar = ivar & 0xFFFF00FF;
			ivar |= (msix_vector | E1000_IVAR_VALID) << 8;
		}
		adapter->tx_ring[tx_queue].eims_value = 1 << msix_vector;
		array_ew32(IVAR0, index, ivar);
	}
}
