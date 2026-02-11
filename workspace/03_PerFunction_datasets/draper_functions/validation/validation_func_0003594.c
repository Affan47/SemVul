GetSMSCenter(gn_data *data, struct gn_statemachine *state)
{
	unsigned char req[] = {FBUS_FRAME_HEADER, 0x33, 0x64, 0x00};
	int id;

	id = data->message_center->id;
	if ((id < 1) || (id > 255)) return GN_ERR_INVALIDLOCATION;

	req[5] = id;

	if (sm_message_send(6, 0x02, req, state)) return GN_ERR_NOTREADY;
	return sm_block(0x02, data, state);
}
