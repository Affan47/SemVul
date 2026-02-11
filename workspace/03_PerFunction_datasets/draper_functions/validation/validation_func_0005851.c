getdatetime(gn_data *data, struct gn_statemachine *state)
{
	gn_timestamp	date_time;
	gn_error	error;

	gn_data_clear(data);
	data->datetime = &date_time;

	error = gn_sm_functions(GN_OP_GetDateTime, data, state);

	switch (error) {
	case GN_ERR_NONE:
		fprintf(stdout, _("Date: %4d/%02d/%02d\n"), date_time.year, date_time.month, date_time.day);
		fprintf(stdout, _("Time: %02d:%02d:%02d\n"), date_time.hour, date_time.minute, date_time.second);
		break;
	default:
		fprintf(stderr, _("Error: %s\n"), gn_error_print(error));
		break;
	}

	return error;
}
