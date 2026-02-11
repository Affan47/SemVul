kv_get_vce_boot_level(struct radeon_device *rdev, u32 evclk)
{
	u8 i;
	struct radeon_vce_clock_voltage_dependency_table *table =
		&rdev->pm.dpm.dyn_state.vce_clock_voltage_dependency_table;

	for (i = 0; i < table->count; i++) {
		if (table->entries[i].evclk >= evclk)
			break;
	}

	return i;
}
