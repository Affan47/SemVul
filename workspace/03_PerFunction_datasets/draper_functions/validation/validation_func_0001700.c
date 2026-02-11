process_boolean_info(const char *nutvalue)
{
	status_lkp_t *status_item;
	int clear = 0;

	upsdebugx(5, "process_boolean_info: %s", nutvalue);

	if (*nutvalue == '!') {
		nutvalue++;
		clear = 1;
	}

	for (status_item = status_info; status_item->status_str != NULL ; status_item++)
	{
		if (strcasecmp(status_item->status_str, nutvalue))
			continue;

		if (clear) {
			ups_status &= ~status_item->status_mask;
		} else {
			ups_status |= status_item->status_mask;
		}

		return;
	}

	upsdebugx(5, "Warning: %s not in list of known values", nutvalue);
}
