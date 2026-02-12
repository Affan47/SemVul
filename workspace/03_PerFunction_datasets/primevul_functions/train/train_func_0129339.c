unsigned long __round_jiffies_relative(unsigned long j, int cpu)
{
	unsigned long j0 = jiffies;


	return round_jiffies_common(j + j0, cpu, false) - j0;
}
