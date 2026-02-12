static bool pmc_overflow_power7(unsigned long val)
{


	if ((0x80000000 - val) <= 256)
		return true;

	return false;
}
