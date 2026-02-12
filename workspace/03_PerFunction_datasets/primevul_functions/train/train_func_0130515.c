static int h2_max_streams(struct connection *conn)
{

	return h2_settings_max_concurrent_streams;
}
