snd_rme96_playback_close(struct snd_pcm_substream *substream)
{
	struct rme96 *rme96 = snd_pcm_substream_chip(substream);
	int spdif = 0;

	spin_lock_irq(&rme96->lock);
	if (RME96_ISPLAYING(rme96)) {
		snd_rme96_trigger(rme96, RME96_STOP_PLAYBACK);
	}
	rme96->playback_substream = NULL;
	rme96->playback_periodsize = 0;
	spdif = (rme96->wcreg & RME96_WCR_ADAT) == 0;
	spin_unlock_irq(&rme96->lock);
	if (spdif) {
		rme96->spdif_ctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		snd_ctl_notify(rme96->card, SNDRV_CTL_EVENT_MASK_VALUE |
			       SNDRV_CTL_EVENT_MASK_INFO, &rme96->spdif_ctl->id);
	}
	return 0;
}
