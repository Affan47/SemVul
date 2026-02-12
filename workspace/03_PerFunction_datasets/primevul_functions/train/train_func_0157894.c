u64 nsecs_to_jiffies64(u64 n)
{
#if (NSEC_PER_SEC % HZ) == 0

	return div_u64(n, NSEC_PER_SEC / HZ);
#elif (HZ % 512) == 0

	return div_u64(n * HZ / 512, NSEC_PER_SEC / 512);
#else


	return div_u64(n * 9, (9ull * NSEC_PER_SEC + HZ / 2) / HZ);
#endif
}
