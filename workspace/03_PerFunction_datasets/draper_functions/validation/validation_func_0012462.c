anti_prehandler (unsigned long best_evtime)
{
	int i, output;
	struct audio_channel_data *acd;


	for (i = 0; i < 4; i++) {
		acd = &audio_channel[i];
		output = (acd->current_sample * acd->vol) & acd->adk_mask;
		acd->sample_accum += output * best_evtime;
		acd->sample_accum_time += best_evtime;
	}
}
