kv_set_thermal_temperature_range(struct radeon_device *rdev,
					    int min_temp, int max_temp)
{
	int low_temp = 0 * 1000;
	int high_temp = 255 * 1000;
	u32 tmp;

	if (low_temp < min_temp)
		low_temp = min_temp;
	if (high_temp > max_temp)
		high_temp = max_temp;
	if (high_temp < low_temp) {
		DRM_ERROR("invalid thermal range: %d - %d\n", low_temp, high_temp);
		return -EINVAL;
	}

	tmp = RREG32_SMC(CG_THERMAL_INT_CTRL);
	tmp &= ~(DIG_THERM_INTH_MASK | DIG_THERM_INTL_MASK);
	tmp |= (DIG_THERM_INTH(49 + (high_temp / 1000)) |
		DIG_THERM_INTL(49 + (low_temp / 1000)));
	WREG32_SMC(CG_THERMAL_INT_CTRL, tmp);

	rdev->pm.dpm.thermal.min_temp = low_temp;
	rdev->pm.dpm.thermal.max_temp = high_temp;

	return 0;
}
