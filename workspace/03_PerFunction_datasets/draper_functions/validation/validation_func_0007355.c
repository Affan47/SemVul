ixgbevf_setup_all_tx_resources(struct ixgbevf_adapter *adapter)
{
	int i, err = 0;

	for (i = 0; i < adapter->num_tx_queues; i++) {
		err = ixgbevf_setup_tx_resources(adapter->tx_ring[i]);
		if (!err)
			continue;
		hw_dbg(&adapter->hw, "Allocation for Tx Queue %u failed\n", i);
		break;
	}

	return err;
}
