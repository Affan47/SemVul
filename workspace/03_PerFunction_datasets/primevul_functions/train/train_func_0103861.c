crypto_time()
{
	l_fp	tstamp;

	L_CLR(&tstamp);
	if (sys_leap != LEAP_NOTINSYNC)
		get_systime(&tstamp);
	return (tstamp.l_ui);
}
