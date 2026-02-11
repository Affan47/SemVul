cpuidle_remove_state_sysfs(struct cpuidle_device *device)
{
	struct cpuidle_driver *drv = cpuidle_get_cpu_driver(device);
	int i;

	for (i = 0; i < drv->state_count; i++)
		cpuidle_free_state_kobj(device, i);
}
