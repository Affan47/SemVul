alloc_common_dbs_info(struct cpufreq_policy *policy,
				 struct common_dbs_data *cdata)
{
	struct cpu_common_dbs_info *shared;
	int j;


	shared = kzalloc(sizeof(*shared), GFP_KERNEL);
	if (!shared)
		return -ENOMEM;


	for_each_cpu(j, policy->related_cpus)
		cdata->get_cpu_cdbs(j)->shared = shared;

	return 0;
}
