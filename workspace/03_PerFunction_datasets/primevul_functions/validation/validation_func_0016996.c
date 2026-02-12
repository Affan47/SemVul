filter_data_next(uint64_t token, uint64_t reqid, const char *line)
{
	struct filter_session  *fs;


	if ((fs = tree_get(&sessions, reqid)) == NULL)
		return;

	filter_data_internal(fs, token, reqid, line);
}
