static int h2_avail_streams(struct connection *conn)
{
	struct h2c *h2c = conn->ctx;


	return (h2_settings_max_concurrent_streams - h2c->nb_streams);
}
