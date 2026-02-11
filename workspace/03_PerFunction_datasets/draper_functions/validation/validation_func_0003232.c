PWM_ACZ_TO_REG(long val, int reg)
{
	int acz = (val == 4) ? 2 : val - 1;

	return (reg & 0x1f) | ((acz & 0x07) << 5);
}
