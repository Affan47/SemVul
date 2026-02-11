update_pb4(int samplerate)
{
	static int counter, level;


	if( sound_latch_b & 0x10 )
	{
		if( level < VMAX )
		{
			counter -= (int)((VMAX - level) / pb4_charge_time);
			if( counter <= 0 )
			{
				int n = (-counter / samplerate) + 1;
				counter += n * samplerate;
				if( (level += n) > VMAX )
					level = VMAX;
			}
		}
	}
	else
	{
		if( level > VMIN )
		{
			counter -= (int)((level - VMIN) / pb4_discharge_time);
			if( counter <= 0 )
			{
				int n = (-counter / samplerate) + 1;
				counter += n * samplerate;
				if( (level -= n) < VMIN)
					level = VMIN;
			}
		}
	}
	return level;
}
