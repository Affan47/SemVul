snd_hda_create_hwdep(struct hda_codec *codec)
{
	char hwname[16];
	struct snd_hwdep *hwdep;
	int err;

	sprintf(hwname, "HDA Codec %d", codec->addr);
	err = snd_hwdep_new(codec->card, hwname, codec->addr, &hwdep);
	if (err < 0)
		return err;
	codec->hwdep = hwdep;
	sprintf(hwdep->name, "HDA Codec %d", codec->addr);
	hwdep->iface = SNDRV_HWDEP_IFACE_HDA;
	hwdep->private_data = codec;
	hwdep->exclusive = 1;

	hwdep->ops.open = hda_hwdep_open;
	hwdep->ops.ioctl = hda_hwdep_ioctl;
#ifdef CONFIG_COMPAT
	hwdep->ops.ioctl_compat = hda_hwdep_ioctl_compat;
#endif


	hwdep->dev.groups = snd_hda_dev_attr_groups;
	dev_set_drvdata(&hwdep->dev, codec);

	return 0;
}
