__padata_add_cpu(struct padata_instance *pinst, int cpu)
{
	struct parallel_data *pd;

	if (cpumask_test_cpu(cpu, cpu_online_mask)) {
		pd = padata_alloc_pd(pinst, pinst->cpumask.pcpu,
				     pinst->cpumask.cbcpu);
		if (!pd)
			return -ENOMEM;

		padata_replace(pinst, pd);

		if (padata_validate_cpumask(pinst, pinst->cpumask.pcpu) &&
		    padata_validate_cpumask(pinst, pinst->cpumask.cbcpu))
			__padata_start(pinst);
	}

	return 0;
}
