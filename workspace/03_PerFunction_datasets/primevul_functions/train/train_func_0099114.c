rndget(void)
{


	return (((lcg_state = 22695477 * lcg_state + 1) >> 16) & 0x7FFF);
}
