trinity_dpm_late_enable(struct radeon_device *rdev)
{
	int ret;

	trinity_acquire_mutex(rdev);
	trinity_enable_clock_power_gating(rdev);

	if (rdev->irq.installed &&
	    r600_is_internal_thermal_sensor(rdev->pm.int_thermal_type)) {
		ret = trinity_set_thermal_temperature_range(rdev, R600_TEMP_RANGE_MIN, R600_TEMP_RANGE_MAX);
		if (ret) {
			trinity_release_mutex(rdev);
			return ret;
		}
		rdev->irq.dpm_thermal = true;
		radeon_irq_set(rdev);
	}
	trinity_release_mutex(rdev);

	return 0;
}
