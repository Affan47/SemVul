AT_GetBattery(gn_data *data, struct gn_statemachine *state)
{
	at_driver_instance *drvinst = AT_DRVINST(state);
	char key[4];

	snprintf(key, 4, "CBC");
	if (map_get(&drvinst->cached_capabilities, key, 1))
		return Parse_ReplyGetBattery(data, state);
	else if (sm_message_send(7, GN_OP_GetBatteryLevel, "AT+CBC\r", state))
		return GN_ERR_NOTREADY;
	return sm_block_no_retry(GN_OP_GetBatteryLevel, data, state);
}
