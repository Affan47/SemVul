mixer_sh_stop(void)
{
	struct mixer_channel_data *channel;
	int i;

	osd_stop_audio_stream();

	for (i = 0, channel = mixer_channel; i < MIXER_MAX_CHANNELS; i++, channel++)
	{
		if (channel->filter)
			filter_free(channel->filter);
		filter_state_free(channel->left);
		filter_state_free(channel->right);
	}
}
