snd_pcm_hw_info(snd_pcm_t *pcm, snd_pcm_info_t * info)
{
	snd_pcm_hw_t *hw = pcm->private_data;
	int fd = hw->fd, err;
	if (ioctl(fd, SNDRV_PCM_IOCTL_INFO, info) < 0) {
		err = -errno;
		SYSMSG("SNDRV_PCM_IOCTL_INFO failed (%i)", err);
		return err;
	}
	return 0;
}
