alc_fixup_headset_mode_alc255_no_hp_mic(struct hda_codec *codec,
				const struct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		struct alc_spec *spec = codec->spec;
		spec->parse_flags |= HDA_PINCFG_HEADSET_MIC;
		alc255_set_default_jack_type(codec);
	}
	else
		alc_fixup_headset_mode(codec, fix, action);
}
