intel_idle_cpu_init(int cpu)
{
	struct cpuidle_device *dev;

	dev = per_cpu_ptr(intel_idle_cpuidle_devices, cpu);

	dev->cpu = cpu;

	if (cpuidle_register_device(dev)) {
		pr_debug(PREFIX "cpuidle_register_device %d failed!\n", cpu);
		intel_idle_cpuidle_devices_uninit();
		return -EIO;
	}

	if (icpu->auto_demotion_disable_flags)
		smp_call_function_single(cpu, auto_demotion_disable, NULL, 1);

	if (icpu->disable_promotion_to_c1e)
		smp_call_function_single(cpu, c1e_promotion_disable, NULL, 1);

	return 0;
}
