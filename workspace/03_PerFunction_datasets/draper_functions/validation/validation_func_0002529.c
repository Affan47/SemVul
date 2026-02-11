snd_card_saa7134_capture_prepare(struct snd_pcm_substream * substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	int bswap, sign;
	u32 fmt, control;
	snd_card_saa7134_t *saa7134 = snd_pcm_substream_chip(substream);
	struct saa7134_dev *dev;
	snd_card_saa7134_pcm_t *pcm = runtime->private_data;

	pcm->dev->dmasound.substream = substream;

	dev = saa7134->dev;

	if (snd_pcm_format_width(runtime->format) == 8)
		fmt = 0x00;
	else
		fmt = 0x01;

	if (snd_pcm_format_signed(runtime->format))
		sign = 1;
	else
		sign = 0;

	if (snd_pcm_format_big_endian(runtime->format))
		bswap = 1;
	else
		bswap = 0;

	switch (dev->pci->device) {
	  case PCI_DEVICE_ID_PHILIPS_SAA7134:
		if (1 == runtime->channels)
			fmt |= (1 << 3);
		if (2 == runtime->channels)
			fmt |= (3 << 3);
		if (sign)
			fmt |= 0x04;

		fmt |= (MIXER_ADDR_TVTUNER == dev->dmasound.input) ? 0xc0 : 0x80;
		saa_writeb(SAA7134_NUM_SAMPLES0, ((dev->dmasound.blksize - 1) & 0x0000ff));
		saa_writeb(SAA7134_NUM_SAMPLES1, ((dev->dmasound.blksize - 1) & 0x00ff00) >>  8);
		saa_writeb(SAA7134_NUM_SAMPLES2, ((dev->dmasound.blksize - 1) & 0xff0000) >> 16);
		saa_writeb(SAA7134_AUDIO_FORMAT_CTRL, fmt);

		break;
	  case PCI_DEVICE_ID_PHILIPS_SAA7133:
	  case PCI_DEVICE_ID_PHILIPS_SAA7135:
		if (1 == runtime->channels)
			fmt |= (1 << 4);
		if (2 == runtime->channels)
			fmt |= (2 << 4);
		if (!sign)
			fmt |= 0x04;
		saa_writel(SAA7133_NUM_SAMPLES, dev->dmasound.blksize -1);
		saa_writel(SAA7133_AUDIO_CHANNEL, 0x543210 | (fmt << 24));
		break;
	}

	pr_debug("rec_start: afmt=%d ch=%d  =>  fmt=0x%x swap=%c\n",
		runtime->format, runtime->channels, fmt,
		bswap ? 'b' : '-');

	control = SAA7134_RS_CONTROL_BURST_16 |
		SAA7134_RS_CONTROL_ME |
		(dev->dmasound.pt.dma >> 12);
	if (bswap)
		control |= SAA7134_RS_CONTROL_BSWAP;

	saa_writel(SAA7134_RS_BA1(6),0);
	saa_writel(SAA7134_RS_BA2(6),dev->dmasound.blksize);
	saa_writel(SAA7134_RS_PITCH(6),0);
	saa_writel(SAA7134_RS_CONTROL(6),control);

	dev->dmasound.rate = runtime->rate;


	snd_saa7134_capsrc_set(saa7134->capture_ctl[dev->dmasound.input], 1, 1,
			       true);

	return 0;

}
