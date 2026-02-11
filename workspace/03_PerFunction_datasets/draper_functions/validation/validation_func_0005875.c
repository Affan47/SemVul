_snd_pcm_share_hwsync(snd_pcm_t *pcm)
{
	snd_pcm_share_t *share = pcm->private_data;
	snd_pcm_share_slave_t *slave = share->slave;
	switch (share->state) {
	case SND_PCM_STATE_XRUN:
		return -EPIPE;
	default:
		break;
	}
	return snd_pcm_hwsync(slave->pcm);
}
