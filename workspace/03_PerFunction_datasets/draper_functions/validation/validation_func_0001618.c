brasero_checksum_image_read (BraseroChecksumImage *self,
			     int fd,
			     guchar *buffer,
			     gint bytes,
			     GError **error)
{
	gint total = 0;
	gint read_bytes;
	BraseroChecksumImagePrivate *priv;

	priv = BRASERO_CHECKSUM_IMAGE_PRIVATE (self);

	while (1) {
		read_bytes = read (fd, buffer + total, (bytes - total));


		if (!read_bytes)
			return total;

		if (priv->cancel)
			return -2;


		if (read_bytes == -1) {
			if (errno != EAGAIN && errno != EINTR) {
                                int errsv = errno;

				g_set_error (error,
					     BRASERO_BURN_ERROR,
					     BRASERO_BURN_ERROR_GENERAL,
					     _("Data could not be read (%s)"),
					     g_strerror (errsv));
				return -1;
			}
		}
		else {
			total += read_bytes;

			if (total == bytes)
				return total;
		}

		g_usleep (500);
	}

	return total;
}
