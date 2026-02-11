si_should_disable_uvd_powertune(struct radeon_device *rdev,
					    struct radeon_ps *radeon_state)
{
	struct si_power_info *si_pi = si_get_pi(rdev);

	if (si_pi->dyn_powertune_data.disable_uvd_powertune &&
	    radeon_state->vclk && radeon_state->dclk)
		return true;

	return false;
}
