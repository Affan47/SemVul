NK7110_DeleteCalendarNote(gn_data *data, struct gn_statemachine *state)
{
	unsigned char req[] = { FBUS_FRAME_HEADER,
				0x0b,
				0x00, 0x00};
	gn_calnote_list list;
	bool own_list = true;

	if (data->calnote_list)
		own_list = false;
	else {
		memset(&list, 0, sizeof(gn_calnote_list));
		data->calnote_list = &list;
	}

	if (data->calnote_list->number == 0)
		NK7110_GetCalendarNotesInfo(data, state);

	if (data->calnote->location < data->calnote_list->number + 1 &&
	    data->calnote->location > 0) {
		req[4] = data->calnote_list->location[data->calnote->location - 1] >> 8;
		req[5] = data->calnote_list->location[data->calnote->location - 1] & 0xff;
	} else {
		return GN_ERR_INVALIDLOCATION;
	}

	if (own_list) data->calnote_list = NULL;
	SEND_MESSAGE_BLOCK(NK7110_MSG_CALENDAR, 6);
}
