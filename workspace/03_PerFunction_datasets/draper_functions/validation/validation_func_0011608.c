fluid_synth_system_reset(fluid_synth_t* synth)
{
	int result;
	fluid_return_val_if_fail (synth != NULL, FLUID_FAILED);
	fluid_synth_api_enter(synth);
	result = fluid_synth_system_reset_LOCAL (synth);
	FLUID_API_RETURN(result);
}
