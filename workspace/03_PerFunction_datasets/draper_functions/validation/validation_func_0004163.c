xmms_oss_open (xmms_output_t *output)
{
	xmms_oss_data_t *data;
	const xmms_config_property_t *val;
	const gchar *dev;
	guint param;

	g_return_val_if_fail (output, FALSE);

	data = xmms_output_private_data_get (output);

	XMMS_DBG ("xmms_oss_open (%p)", output);

	val = xmms_output_config_lookup (output, "device");
	dev = xmms_config_property_get_string (val);

	data->fd = open (dev, O_RDWR);
	if (data->fd == -1)
		return FALSE;

	param = (32 << 16) | 0xC;
	if (ioctl (data->fd, SNDCTL_DSP_SETFRAGMENT, &param) == -1)
		goto error;

	if (data->oss4_mixer) {

		data->have_mixer = TRUE;
	}

	return TRUE;

error:
	close (data->fd);
	if (data->mixer_fd != -1)
		close (data->mixer_fd);
	g_free (data);
	return FALSE;

}
