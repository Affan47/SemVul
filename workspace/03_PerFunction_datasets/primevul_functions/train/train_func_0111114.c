static void __fib6_drop_pcpu_from(struct fib6_nh *fib6_nh,
				  const struct fib6_info *match,
				  const struct fib6_table *table)
{
	int cpu;

	if (!fib6_nh->rt6i_pcpu)
		return;


	for_each_possible_cpu(cpu) {
		struct rt6_info **ppcpu_rt;
		struct rt6_info *pcpu_rt;

		ppcpu_rt = per_cpu_ptr(fib6_nh->rt6i_pcpu, cpu);
		pcpu_rt = *ppcpu_rt;


		if (pcpu_rt && rcu_access_pointer(pcpu_rt->from) == match) {
			struct fib6_info *from;

			from = xchg((__force struct fib6_info **)&pcpu_rt->from, NULL);
			fib6_info_release(from);
		}
	}
}
