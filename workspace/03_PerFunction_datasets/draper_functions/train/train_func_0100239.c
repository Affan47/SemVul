calc_pitch_shift_adip(int amount)
{
	int val = (amount * 0x1b4f) >> 16;
	if (val < -128) val = -128;
	else if (val > 127) val = 127;
	if (val < 0)
		return 0x100 + val;
	else
		return val;
}
