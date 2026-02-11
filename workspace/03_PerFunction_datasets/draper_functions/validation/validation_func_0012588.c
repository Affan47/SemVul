olpc_xo_mic_boost_put(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct conexant_spec *spec = codec->spec;
	int ret = snd_hda_mixer_amp_volume_put(kcontrol, ucontrol);
	if (ret > 0 && spec->dc_enable)
		olpc_xo_update_mic_boost(codec);
	return ret;
}
