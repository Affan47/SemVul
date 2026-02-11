set_cpu_sibling_map(int cpu)
{
	bool has_smt = smp_num_siblings > 1;
	bool has_mp = has_smt || boot_cpu_data.x86_max_cores > 1;
	struct cpuinfo_x86 *c = &cpu_data(cpu);
	struct cpuinfo_x86 *o;
	int i;

	cpumask_set_cpu(cpu, cpu_sibling_setup_mask);

	if (!has_mp) {
		cpumask_set_cpu(cpu, topology_sibling_cpumask(cpu));
		cpumask_set_cpu(cpu, cpu_llc_shared_mask(cpu));
		cpumask_set_cpu(cpu, topology_core_cpumask(cpu));
		c->booted_cores = 1;
		return;
	}

	for_each_cpu(i, cpu_sibling_setup_mask) {
		o = &cpu_data(i);

		if ((i == cpu) || (has_smt && match_smt(c, o)))
			link_mask(topology_sibling_cpumask, cpu, i);

		if ((i == cpu) || (has_mp && match_llc(c, o)))
			link_mask(cpu_llc_shared_mask, cpu, i);

	}


	for_each_cpu(i, cpu_sibling_setup_mask) {
		o = &cpu_data(i);

		if ((i == cpu) || (has_mp && match_die(c, o))) {
			link_mask(topology_core_cpumask, cpu, i);


			if (cpumask_weight(
			    topology_sibling_cpumask(cpu)) == 1) {


				if (cpumask_first(
				    topology_sibling_cpumask(i)) == i)
					c->booted_cores++;


				if (i != cpu)
					cpu_data(i).booted_cores++;
			} else if (i != cpu && !c->booted_cores)
				c->booted_cores = cpu_data(i).booted_cores;
		}
		if (match_die(c, o) && !topology_same_node(c, o))
			primarily_use_numa_for_topology();
	}
}
