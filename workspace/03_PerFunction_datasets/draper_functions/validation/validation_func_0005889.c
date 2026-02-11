snd_hda_gen_update_outputs(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	int *paths;
	int on;


	if (spec->autocfg.line_out_type == AUTO_PIN_HP_OUT)
		paths = spec->out_paths;
	else
		paths = spec->hp_paths;
	do_automute(codec, ARRAY_SIZE(spec->autocfg.hp_pins),
		    spec->autocfg.hp_pins, paths, spec->master_mute);

	if (!spec->automute_speaker)
		on = 0;
	else
		on = spec->hp_jack_present | spec->line_jack_present;
	on |= spec->master_mute;
	spec->speaker_muted = on;
	if (spec->autocfg.line_out_type == AUTO_PIN_SPEAKER_OUT)
		paths = spec->out_paths;
	else
		paths = spec->speaker_paths;
	do_automute(codec, ARRAY_SIZE(spec->autocfg.speaker_pins),
		    spec->autocfg.speaker_pins, paths, on);


	if (spec->autocfg.line_out_pins[0] == spec->autocfg.hp_pins[0] ||
	    spec->autocfg.line_out_pins[0] == spec->autocfg.speaker_pins[0])
		return;
	if (!spec->automute_lo)
		on = 0;
	else
		on = spec->hp_jack_present;
	on |= spec->master_mute;
	spec->line_out_muted = on;
	paths = spec->out_paths;
	do_automute(codec, ARRAY_SIZE(spec->autocfg.line_out_pins),
		    spec->autocfg.line_out_pins, paths, on);
}
