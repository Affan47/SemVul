si_disable_ulv(struct radeon_device *rdev)
{
	struct si_power_info *si_pi = si_get_pi(rdev);
	struct si_ulv_param *ulv = &si_pi->ulv;

	if (ulv->supported)
		return (si_send_msg_to_smc(rdev, PPSMC_MSG_DisableULV) == PPSMC_Result_OK) ?
			0 : -EINVAL;

	return 0;
}
