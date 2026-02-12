jiffies_to_timespec64(const unsigned long jiffies, struct timespec64 *value)
{


	u32 rem;
	value->tv_sec = div_u64_rem((u64)jiffies * TICK_NSEC,
				    NSEC_PER_SEC, &rem);
	value->tv_nsec = rem;
}
