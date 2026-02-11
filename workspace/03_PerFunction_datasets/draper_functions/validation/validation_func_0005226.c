ni_dpm_get_sclk(struct radeon_device *rdev, bool low)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct ni_ps *requested_state = ni_get_ps(&eg_pi->requested_rps);

	if (low)
		return requested_state->performance_levels[0].sclk;
	else
		return requested_state->performance_levels[requested_state->performance_level_count - 1].sclk;
}
