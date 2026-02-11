fluid_synth_set_gen2(fluid_synth_t* synth, int chan, int param,
                     float value, int absolute, int normalized)
{
	float v;
	fluid_return_val_if_fail (param >= 0 && param < GEN_LAST, FLUID_FAILED);
	FLUID_API_ENTRY_CHAN(FLUID_FAILED);

	v = normalized ? fluid_gen_scale(param, value) : value;

	fluid_synth_set_gen_LOCAL (synth, chan, param, v, absolute);

	FLUID_API_RETURN(FLUID_OK);
}
