g_io_gnutls_set_flags(GIOChannel *channel,
						GIOFlags flags, GError **err)
{
	GIOGnuTLSChannel *gnutls_channel = (GIOGnuTLSChannel *) channel;
	glong fcntl_flags = 0;

	DBG("channel %p flags %u", channel, flags);

	if (flags & G_IO_FLAG_NONBLOCK)
		fcntl_flags |= O_NONBLOCK;

	if (fcntl(gnutls_channel->fd, F_SETFL, fcntl_flags) < 0) {
		g_set_error_literal(err, G_IO_CHANNEL_ERROR,
			G_IO_CHANNEL_ERROR_FAILED, "Setting flags failed");
		return G_IO_STATUS_ERROR;
	}

	return G_IO_STATUS_NORMAL;
}
