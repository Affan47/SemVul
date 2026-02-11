cz_dpm_update_low_memory_pstate(struct amdgpu_device *adev)
{
	int ret = 0;
	struct cz_power_info *pi = cz_get_pi(adev);
	struct cz_ps *ps = &pi->requested_ps;

	if (pi->sys_info.nb_dpm_enable) {
		if (ps->force_high)
			cz_dpm_nbdpm_lm_pstate_enable(adev, false);
		else
			cz_dpm_nbdpm_lm_pstate_enable(adev, true);
	}

	return ret;
}
