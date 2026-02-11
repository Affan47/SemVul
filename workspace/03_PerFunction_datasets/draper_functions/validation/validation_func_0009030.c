intel_dp_encoder_suspend(struct intel_encoder *intel_encoder)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(&intel_encoder->base);

	if (!is_edp(intel_dp))
		return;


	cancel_delayed_work_sync(&intel_dp->panel_vdd_work);
	pps_lock(intel_dp);
	edp_panel_vdd_off_sync(intel_dp);
	pps_unlock(intel_dp);
}
