snd_pcm_hw_params_choose(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
	int err;
#ifdef CHOOSE_DEBUG
	snd_output_t *log;
	snd_output_stdio_attach(&log, stderr, 0);
	snd_output_printf(log, "CHOOSE called:\n");
	snd_pcm_hw_params_dump(params, log);
#endif

	err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_ACCESS, NULL, 0);
	if (err < 0)
		return err;
	err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_FORMAT, NULL, 0);
	if (err < 0)
		return err;
	err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_SUBFORMAT, NULL, 0);
	if (err < 0)
		return err;
	err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_CHANNELS, NULL, 0);
	if (err < 0)
		return err;
	err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_RATE, NULL, 0);
	if (err < 0)
		return err;
	if (pcm->minperiodtime > 0) {
		unsigned int min, max;
		int dir = 1;
		err = snd_pcm_hw_param_get_min(params, SND_PCM_HW_PARAM_PERIOD_TIME, &min, &dir);
		if (err >= 0)
			err = snd_pcm_hw_param_get_max(params, SND_PCM_HW_PARAM_PERIOD_TIME, &max, &dir);
		if (err >= 0 && (long)min < pcm->minperiodtime &&
			        (long)max > pcm->minperiodtime) {
			min = pcm->minperiodtime; dir = 1;
			snd_pcm_hw_param_set_min(pcm, params, SND_CHANGE, SND_PCM_HW_PARAM_PERIOD_TIME, &min, &dir);
		}
	}
	if (pcm->compat) {

		err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_PERIOD_TIME, NULL, 0);
		if (err < 0)
			return err;
		err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_PERIOD_SIZE, NULL, 0);
		if (err < 0)
			return err;
		err = snd_pcm_hw_param_set_last(pcm, params, SND_PCM_HW_PARAM_BUFFER_SIZE, NULL, 0);
		if (err < 0)
			return err;
	} else {

		err = snd_pcm_hw_param_set_last(pcm, params, SND_PCM_HW_PARAM_BUFFER_SIZE, NULL, 0);
		if (err < 0)
			return err;
		err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_PERIOD_SIZE, NULL, 0);
		if (err < 0)
			return err;
		err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_PERIOD_TIME, NULL, 0);
		if (err < 0)
			return err;
	}
	err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_TICK_TIME, NULL, 0);
	if (err < 0)
		return err;
#ifdef CHOOSE_DEBUG
	snd_output_printf(log, "choose done\n");
	snd_pcm_hw_params_dump(params, log);
	snd_output_close(log);
#endif
	return 0;
}
