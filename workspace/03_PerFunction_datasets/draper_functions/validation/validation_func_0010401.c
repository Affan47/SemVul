ak4641_put_deemph(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_soc_kcontrol_codec(kcontrol);
	struct ak4641_priv *ak4641 = snd_soc_codec_get_drvdata(codec);
	int deemph = ucontrol->value.integer.value[0];

	if (deemph > 1)
		return -EINVAL;

	ak4641->deemph = deemph;

	return ak4641_set_deemph(codec);
}
