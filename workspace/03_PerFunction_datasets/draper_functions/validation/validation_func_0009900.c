snd_hda_gen_line_automute(struct hda_codec *codec,
			       struct hda_jack_callback *jack)
{
	struct hda_gen_spec *spec = codec->spec;

	if (spec->autocfg.line_out_type == AUTO_PIN_SPEAKER_OUT)
		return;

	if (spec->autocfg.line_out_pins[0] == spec->autocfg.hp_pins[0])
		return;

	spec->line_jack_present =
		detect_jacks(codec, ARRAY_SIZE(spec->autocfg.line_out_pins),
			     spec->autocfg.line_out_pins);
	if (!spec->automute_speaker || !spec->detect_lo)
		return;
	call_update_outputs(codec);
}
