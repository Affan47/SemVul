auto_mic_check_imux(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	const struct hda_input_mux *imux;
	int i;

	imux = &spec->input_mux;
	for (i = 0; i < spec->am_num_entries; i++) {
		spec->am_entry[i].idx =
			find_idx_in_nid_list(spec->am_entry[i].pin,
					     spec->imux_pins, imux->num_items);
		if (spec->am_entry[i].idx < 0)
			return false;
	}


	for (i = 1; i < spec->am_num_entries; i++)
		snd_hda_jack_detect_enable_callback(codec,
						    spec->am_entry[i].pin,
						    call_mic_autoswitch);
	return true;
}
