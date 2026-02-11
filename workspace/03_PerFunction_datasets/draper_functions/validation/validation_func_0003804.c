acpi_processor_cst_has_changed(struct acpi_processor *pr)
{
	int cpu;
	struct acpi_processor *_pr;
	struct cpuidle_device *dev;

	if (disabled_by_idle_boot_param())
		return 0;

	if (nocst)
		return -ENODEV;

	if (!pr->flags.power_setup_done)
		return -ENODEV;


	if (pr->id == 0 && cpuidle_get_driver() == &acpi_idle_driver) {


		get_online_cpus();
		cpuidle_pause_and_lock();


		for_each_online_cpu(cpu) {
			_pr = per_cpu(processors, cpu);
			if (!_pr || !_pr->flags.power_setup_done)
				continue;
			dev = per_cpu(acpi_cpuidle_device, cpu);
			cpuidle_disable_device(dev);
		}


		acpi_processor_get_power_info(pr);
		acpi_processor_setup_cpuidle_states(pr);


		for_each_online_cpu(cpu) {
			_pr = per_cpu(processors, cpu);
			if (!_pr || !_pr->flags.power_setup_done)
				continue;
			acpi_processor_get_power_info(_pr);
			if (_pr->flags.power) {
				dev = per_cpu(acpi_cpuidle_device, cpu);
				acpi_processor_setup_cpuidle_cx(_pr, dev);
				cpuidle_enable_device(dev);
			}
		}
		cpuidle_resume_and_unlock();
		put_online_cpus();
	}

	return 0;
}
