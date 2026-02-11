arc4random64(void)
{
	uint32 hi, lo;

	THREAD_LOCK;
	arc4_check_stir();
	hi = arc4_getword(&rs);
	lo = arc4_getword(&rs);
	THREAD_UNLOCK;

	return ((uint64) hi << 32) | (uint64) lo;
}
