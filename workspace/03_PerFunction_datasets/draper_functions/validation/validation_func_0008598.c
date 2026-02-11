afp_getvolparms_reply(struct afp_server *server, char * buf, unsigned int size,void * other)
{
	unsigned int bitmap;
	struct afp_volume *volume = (void *) other;

	struct {
		struct dsi_header dsi_header __attribute__((__packed__));
		uint16_t bitmap;
	}  __attribute__((__packed__)) * reply = (void *) buf;

	if (size < sizeof (*reply))
		return -1;

	bitmap = ntohs(reply->bitmap);

	if (!volume) {
		log_for_client(NULL,AFPFSD,LOG_WARNING,"I don't know what volume this is\n");
		return -1;
	}


	if (parse_volbitmap_reply(server,volume,
		bitmap, buf+sizeof(*reply),
			size-sizeof(*reply))!=0)
		return -1;

	return 0;

}
