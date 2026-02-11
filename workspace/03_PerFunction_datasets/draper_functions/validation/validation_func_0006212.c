sample16i_rh_handler (void)
{
	unsigned long delta, ratio;

	uae_u32 data0 = audio_channel[0].current_sample;
	uae_u32 data1 = audio_channel[1].current_sample;
	uae_u32 data2 = audio_channel[2].current_sample;
	uae_u32 data3 = audio_channel[3].current_sample;
	uae_u32 data0p = audio_channel[0].last_sample;
	uae_u32 data1p = audio_channel[1].last_sample;
	uae_u32 data2p = audio_channel[2].last_sample;
	uae_u32 data3p = audio_channel[3].last_sample;
	uae_u32 data;

	DO_CHANNEL_1 (data0, 0);
	DO_CHANNEL_1 (data1, 1);
	DO_CHANNEL_1 (data2, 2);
	DO_CHANNEL_1 (data3, 3);
	DO_CHANNEL_1 (data0p, 0);
	DO_CHANNEL_1 (data1p, 1);
	DO_CHANNEL_1 (data2p, 2);
	DO_CHANNEL_1 (data3p, 3);

	data0 &= audio_channel[0].adk_mask;
	data0p &= audio_channel[0].adk_mask;
	data1 &= audio_channel[1].adk_mask;
	data1p &= audio_channel[1].adk_mask;
	data2 &= audio_channel[2].adk_mask;
	data2p &= audio_channel[2].adk_mask;
	data3 &= audio_channel[3].adk_mask;
	data3p &= audio_channel[3].adk_mask;


	delta = audio_channel[0].per;
	ratio = ((audio_channel[0].evtime % delta) << 8) / delta;
	data0 = (data0 * (256 - ratio) + data0p * ratio) >> 8;
	delta = audio_channel[1].per;
	ratio = ((audio_channel[1].evtime % delta) << 8) / delta;
	data0 += (data1 * (256 - ratio) + data1p * ratio) >> 8;
	delta = audio_channel[2].per;
	ratio = ((audio_channel[2].evtime % delta) << 8) / delta;
	data0 += (data2 * (256 - ratio) + data2p * ratio) >> 8;
	delta = audio_channel[3].per;
	ratio = ((audio_channel[3].evtime % delta) << 8) / delta;
	data0 += (data3 * (256 - ratio) + data3p * ratio) >> 8;
	data = SBASEVAL16(2) + data0;
	data = FINISH_DATA (data, 16);
	set_sound_buffers ();
	PUT_SOUND_WORD_MONO (data);
	check_sound_buffers ();
}
