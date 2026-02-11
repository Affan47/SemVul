WritePhonebook(gn_data *data, struct gn_statemachine *state)
{
	if (writephonebook == NULL)
		return GN_ERR_UNKNOWN;
	if (data->memory_status && data->memory_status->memory_type == GN_MT_ME)
		return GN_ERR_NOTSUPPORTED;
	return (*writephonebook)(data, state);
}
