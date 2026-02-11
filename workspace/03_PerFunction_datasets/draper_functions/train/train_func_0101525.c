snd_emu10k1_pcm_mixer_notify1(struct snd_emu10k1 *emu, struct snd_kcontrol *kctl, int idx, int activate)
{
	struct snd_ctl_elem_id id;

	if (! kctl)
		return;
	if (activate)
		kctl->vd[idx].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	else
		kctl->vd[idx].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notify(emu->card, SNDRV_CTL_EVENT_MASK_VALUE |
		       SNDRV_CTL_EVENT_MASK_INFO,
		       snd_ctl_build_ioff(&id, kctl, idx));
}
