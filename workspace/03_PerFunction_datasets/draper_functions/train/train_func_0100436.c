xen_hvm_cpu_up(unsigned int cpu, struct task_struct *tidle)
{
	int rc;


	if (cpu_report_state(cpu) == CPU_DEAD_FROZEN) {
		xen_smp_intr_free(cpu);
		xen_uninit_lock_cpu(cpu);
	}


	rc = xen_smp_intr_init(cpu);
	WARN_ON(rc);
	if (!rc)
		rc =  native_cpu_up(cpu, tidle);


	xen_init_lock_cpu(cpu);
	return rc;
}
