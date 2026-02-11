hiface_pcm_open(struct snd_pcm_substream *alsa_sub)
{
	struct pcm_runtime *rt = snd_pcm_substream_chip(alsa_sub);
	struct pcm_substream *sub = NULL;
	struct snd_pcm_runtime *alsa_rt = alsa_sub->runtime;
	int ret;

	if (rt->panic)
		return -EPIPE;

	mutex_lock(&rt->stream_mutex);
	alsa_rt->hw = pcm_hw;

	if (alsa_sub->stream == SNDRV_PCM_STREAM_PLAYBACK)
		sub = &rt->playback;

	if (!sub) {
		struct device *device = &rt->chip->dev->dev;
		mutex_unlock(&rt->stream_mutex);
		dev_err(device, "Invalid stream type\n");
		return -EINVAL;
	}

	if (rt->extra_freq) {
		alsa_rt->hw.rates |= SNDRV_PCM_RATE_KNOT;
		alsa_rt->hw.rate_max = 384000;


		ret = snd_pcm_hw_constraint_list(alsa_sub->runtime, 0,
						 SNDRV_PCM_HW_PARAM_RATE,
						 &constraints_extra_rates);
		if (ret < 0) {
			mutex_unlock(&rt->stream_mutex);
			return ret;
		}
	}

	sub->instance = alsa_sub;
	sub->active = false;
	mutex_unlock(&rt->stream_mutex);
	return 0;
}
