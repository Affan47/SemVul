build_all_zonelists_init(void)
{
	int cpu;

	__build_all_zonelists(NULL);


	for_each_possible_cpu(cpu)
		setup_pageset(&per_cpu(boot_pageset, cpu), 0);

	mminit_verify_zonelist();
	cpuset_init_current_mems_allowed();
}
