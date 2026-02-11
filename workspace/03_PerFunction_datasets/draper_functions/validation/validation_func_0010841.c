bt_add_announce(torrent_ctx *ctx, const char* announce_url)
{
	char* url_copy;
	if (!announce_url || announce_url[0] == '\0') return 0;
	url_copy = strdup(announce_url);
	if (!url_copy) return 0;
	return bt_vector_add_ptr(&ctx->announce, url_copy);
}
