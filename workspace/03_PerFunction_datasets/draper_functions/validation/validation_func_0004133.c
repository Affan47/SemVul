get_cw_time(int cw_min, int cw_max, int retries, int slottime)
{
	int cw = pow(2, (cw_min + retries)) - 1;
	cw_max = pow(2, cw_max) - 1;

	if(cw >  cw_max)
		cw = cw_max;

	DEBUG("CW min %d max %d ret %d = %d\n", cw_min, cw_max, retries, cw);
	return (cw * slottime) / 2;
}
