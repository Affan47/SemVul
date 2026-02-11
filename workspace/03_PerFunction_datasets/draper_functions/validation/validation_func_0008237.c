sigmadsp_attach(struct sigmadsp *sigmadsp,
	struct snd_soc_component *component)
{
	struct sigmadsp_control *ctrl;
	unsigned int samplerate_mask;
	int ret;

	sigmadsp->component = component;

	samplerate_mask = sigmadsp_get_samplerate_mask(sigmadsp,
		sigmadsp->current_samplerate);

	list_for_each_entry(ctrl, &sigmadsp->ctrl_list, head) {
		ret = sigmadsp_alloc_control(sigmadsp, ctrl, samplerate_mask);
		if (ret)
			return ret;
	}

	return 0;
}
