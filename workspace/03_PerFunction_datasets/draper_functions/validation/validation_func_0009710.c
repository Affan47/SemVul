save_state( vrc6_apu_state_t* out ) const
{
	assert( sizeof (vrc6_apu_state_t) == 20 );
	out->saw_amp = oscs [2].amp;
	for ( int i = 0; i < osc_count; i++ )
	{
		Vrc6_Osc const& osc = oscs [i];
		for ( int r = 0; r < reg_count; r++ )
			out->regs [i] [r] = osc.regs [r];

		out->delays [i] = osc.delay;
		out->phases [i] = osc.phase;
	}
}
