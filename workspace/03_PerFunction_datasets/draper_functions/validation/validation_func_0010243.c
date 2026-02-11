dapm_widget_show_component(struct snd_soc_component *cmpnt,
	char *buf)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	struct snd_soc_dapm_widget *w;
	int count = 0;
	char *state = "not set";


	if (!cmpnt->card)
		return 0;

	list_for_each_entry(w, &cmpnt->card->widgets, list) {
		if (w->dapm != dapm)
			continue;


		switch (w->id) {
		case snd_soc_dapm_hp:
		case snd_soc_dapm_mic:
		case snd_soc_dapm_spk:
		case snd_soc_dapm_line:
		case snd_soc_dapm_micbias:
		case snd_soc_dapm_dac:
		case snd_soc_dapm_adc:
		case snd_soc_dapm_pga:
		case snd_soc_dapm_out_drv:
		case snd_soc_dapm_mixer:
		case snd_soc_dapm_mixer_named_ctl:
		case snd_soc_dapm_supply:
		case snd_soc_dapm_regulator_supply:
		case snd_soc_dapm_clock_supply:
			if (w->name)
				count += sprintf(buf + count, "%s: %s\n",
					w->name, w->power ? "On":"Off");
		break;
		default:
		break;
		}
	}

	switch (snd_soc_dapm_get_bias_level(dapm)) {
	case SND_SOC_BIAS_ON:
		state = "On";
		break;
	case SND_SOC_BIAS_PREPARE:
		state = "Prepare";
		break;
	case SND_SOC_BIAS_STANDBY:
		state = "Standby";
		break;
	case SND_SOC_BIAS_OFF:
		state = "Off";
		break;
	}
	count += sprintf(buf + count, "PM State: %s\n", state);

	return count;
}
