brasero_dvdcss_write_sector_to_fd (BraseroDvdcss *self,
				   gpointer buffer,
				   gint bytes_remaining)
{
	int fd;
	gint bytes_written = 0;
	BraseroDvdcssPrivate *priv;

	priv = BRASERO_DVDCSS_PRIVATE (self);

	brasero_job_get_fd_out (BRASERO_JOB (self), &fd);
	while (bytes_remaining) {
		gint written;

		written = write (fd,
				 ((gchar *) buffer)  + bytes_written,
				 bytes_remaining);

		if (priv->cancel)
			break;

		if (written != bytes_remaining) {
			if (errno != EINTR && errno != EAGAIN) {
                                int errsv = errno;


				priv->error = g_error_new (BRASERO_BURN_ERROR,
							   BRASERO_BURN_ERROR_GENERAL,
							   _("Data could not be written (%s)"),
							   g_strerror (errsv));
				return BRASERO_BURN_ERR;
			}

			g_thread_yield ();
		}

		if (written > 0) {
			bytes_remaining -= written;
			bytes_written += written;
		}
	}

	return BRASERO_BURN_OK;
}
