sony_nc_rfkill_update(void)
{
	enum sony_nc_rfkill i;
	int result;
	bool hwblock;

	sony_call_snc_handle(sony_rfkill_handle, 0x200, &result);
	hwblock = !(result & 0x1);

	for (i = 0; i < N_SONY_RFKILL; i++) {
		int argument = sony_rfkill_address[i];

		if (!sony_rfkill_devices[i])
			continue;

		if (hwblock) {
			if (rfkill_set_hw_state(sony_rfkill_devices[i], true)) {

			}
			continue;
		}

		sony_call_snc_handle(sony_rfkill_handle, argument, &result);
		rfkill_set_states(sony_rfkill_devices[i],
				  !(result & 0x2), false);
	}
}
