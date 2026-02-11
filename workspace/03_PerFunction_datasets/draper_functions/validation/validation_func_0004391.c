soc_probe_link_components(struct snd_soc_card *card, int num,
				     int order)
{
	struct snd_soc_pcm_runtime *rtd = &card->rtd[num];
	struct snd_soc_platform *platform = rtd->platform;
	struct snd_soc_component *component;
	int i, ret;


	component = rtd->cpu_dai->component;
	if (component->driver->probe_order == order) {
		ret = soc_probe_component(card, component);
		if (ret < 0)
			return ret;
	}


	for (i = 0; i < rtd->num_codecs; i++) {
		component = rtd->codec_dais[i]->component;
		if (component->driver->probe_order == order) {
			ret = soc_probe_component(card, component);
			if (ret < 0)
				return ret;
		}
	}


	if (platform->component.driver->probe_order == order) {
		ret = soc_probe_component(card, &platform->component);
		if (ret < 0)
			return ret;
	}

	return 0;
}
