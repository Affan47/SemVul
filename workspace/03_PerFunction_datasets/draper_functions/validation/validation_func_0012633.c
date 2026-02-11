ci_populate_smc_mvdd_table(struct amdgpu_device *adev,
				      SMU7_Discrete_DpmTable *table)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	unsigned int count;

	table->MvddLevelCount = pi->mvdd_voltage_table.count;
	for (count = 0; count < table->MvddLevelCount; count++) {
		ci_populate_smc_voltage_table(adev,
					      &pi->mvdd_voltage_table.entries[count],
					      &table->MvddLevel[count]);

		if (pi->mvdd_control == CISLANDS_VOLTAGE_CONTROL_BY_GPIO)
			table->MvddLevel[count].Smio |=
				pi->mvdd_voltage_table.entries[count].smio_low;
		else
			table->MvddLevel[count].Smio = 0;
	}
	table->MvddLevelCount = cpu_to_be32(table->MvddLevelCount);

	return 0;
}
