raop_client_set_volume (raop_client_t *rc, gdouble volume)
{
	rc->volume = volume;
	if (rc->rtsp_state & RAOP_RTSP_CONNECTED) {
		rc->rtsp_state |= RAOP_RTSP_SETPARAMS;
		rc->io_state |= RAOP_IO_RTSP_WRITE;
	}
	return RAOP_EOK;
}
