static int acp_poweroff(struct generic_pm_domain *genpd)
{
	struct acp_pm_domain *apd;
	struct amdgpu_device *adev;

	apd = container_of(genpd, struct acp_pm_domain, gpd);
	if (apd != NULL) {
		adev = apd->adev;


		if (adev->powerplay.pp_funcs &&
			adev->powerplay.pp_funcs->set_powergating_by_smu)
			amdgpu_dpm_set_powergating_by_smu(adev, AMD_IP_BLOCK_TYPE_ACP, true);
	}
	return 0;
}
