fluid_voice_modulate(fluid_voice_t* voice, int cc, int ctrl)
{
	int i, k;
	fluid_mod_t* mod;
	int gen;
	fluid_real_t modval;


	for (i = 0; i < voice->mod_count; i++) {

		mod = &voice->mod[i];


		if (fluid_mod_has_source(mod, cc, ctrl)) {

			gen = fluid_mod_get_dest(mod);
			modval = 0.0;


			for (k = 0; k < voice->mod_count; k++) {
				if (fluid_mod_has_dest(&voice->mod[k], gen)) {
					modval += fluid_mod_get_value(&voice->mod[k], voice->channel, voice);
				}
			}

			fluid_gen_set_mod(&voice->gen[gen], modval);


			fluid_voice_update_param(voice, gen);
		}
	}
	return FLUID_OK;
}
