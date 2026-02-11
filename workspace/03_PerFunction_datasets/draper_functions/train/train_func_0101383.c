pcxhr_monitor_vol_put(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	int changed = 0;
	int i;

	mutex_lock(&chip->mgr->mixer_mutex);
	for (i = 0; i < 2; i++) {
		if (chip->monitoring_volume[i] !=
		    ucontrol->value.integer.value[i]) {
			chip->monitoring_volume[i] =
				ucontrol->value.integer.value[i];
			if (chip->monitoring_active[i])


				pcxhr_update_audio_pipe_level(chip, 0, i);
			changed = 1;
		}
	}
	mutex_unlock(&chip->mgr->mixer_mutex);
	return changed;
}
