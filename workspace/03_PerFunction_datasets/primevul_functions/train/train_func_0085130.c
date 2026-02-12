InitProcessGlobals(void)
{
	unsigned int rseed;

	MyProcPid = getpid();
	MyStartTimestamp = GetCurrentTimestamp();
	MyStartTime = timestamptz_to_time_t(MyStartTimestamp);


	if (!pg_strong_random(&rseed, sizeof(rseed)))
	{


		rseed = ((uint64) MyProcPid) ^
			((uint64) MyStartTimestamp << 12) ^
			((uint64) MyStartTimestamp >> 20);
	}
	srandom(rseed);
}
