reg_to_pwm_enable(int pwm, int mode)
{
	if (mode == 0 && pwm == 255)
		return off;
	return mode + 1;
}
