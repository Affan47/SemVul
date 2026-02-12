static void pcpu_init_value(struct bpf_htab *htab, void __percpu *pptr,
			    void *value, bool onallcpus)
{


	if (htab_is_prealloc(htab) && !onallcpus) {
		u32 size = round_up(htab->map.value_size, 8);
		int current_cpu = raw_smp_processor_id();
		int cpu;

		for_each_possible_cpu(cpu) {
			if (cpu == current_cpu)
				bpf_long_memcpy(per_cpu_ptr(pptr, cpu), value,
						size);
			else
				memset(per_cpu_ptr(pptr, cpu), 0, size);
		}
	} else {
		pcpu_copy_value(htab, pptr, value, onallcpus);
	}
}
