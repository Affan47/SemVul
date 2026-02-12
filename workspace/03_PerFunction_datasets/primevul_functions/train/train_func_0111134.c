static void fib6_drop_pcpu_from(struct fib6_info *f6i,
				const struct fib6_table *table)
{


	f6i->fib6_destroying = 1;
	mb();

	if (f6i->nh) {
		struct fib6_nh_pcpu_arg arg = {
			.from = f6i,
			.table = table
		};

		nexthop_for_each_fib6_nh(f6i->nh, fib6_nh_drop_pcpu_from,
					 &arg);
	} else {
		struct fib6_nh *fib6_nh;

		fib6_nh = f6i->fib6_nh;
		__fib6_drop_pcpu_from(fib6_nh, f6i, table);
	}
}
