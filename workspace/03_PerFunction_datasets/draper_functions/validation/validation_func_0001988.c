ixgbevf_tx_timeout_reset(struct ixgbevf_adapter *adapter)
{

	if (!test_bit(__IXGBEVF_DOWN, &adapter->state)) {
		set_bit(__IXGBEVF_RESET_REQUESTED, &adapter->state);
		ixgbevf_service_event_schedule(adapter);
	}
}
