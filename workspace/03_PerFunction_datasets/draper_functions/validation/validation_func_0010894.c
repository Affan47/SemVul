ath10k_mac_set_fixed_rate_params(struct ath10k_vif *arvif,
					    u8 rate, u8 nss, u8 sgi, u8 ldpc)
{
	struct ath10k *ar = arvif->ar;
	u32 vdev_param;
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac set fixed rate params vdev %i rate 0x%02hhx nss %hhu sgi %hhu\n",
		   arvif->vdev_id, rate, nss, sgi);

	vdev_param = ar->wmi.vdev_param->fixed_rate;
	ret = ath10k_wmi_vdev_set_param(ar, arvif->vdev_id, vdev_param, rate);
	if (ret) {
		ath10k_warn(ar, "failed to set fixed rate param 0x%02x: %d\n",
			    rate, ret);
		return ret;
	}

	vdev_param = ar->wmi.vdev_param->nss;
	ret = ath10k_wmi_vdev_set_param(ar, arvif->vdev_id, vdev_param, nss);
	if (ret) {
		ath10k_warn(ar, "failed to set nss param %d: %d\n", nss, ret);
		return ret;
	}

	vdev_param = ar->wmi.vdev_param->sgi;
	ret = ath10k_wmi_vdev_set_param(ar, arvif->vdev_id, vdev_param, sgi);
	if (ret) {
		ath10k_warn(ar, "failed to set sgi param %d: %d\n", sgi, ret);
		return ret;
	}

	vdev_param = ar->wmi.vdev_param->ldpc;
	ret = ath10k_wmi_vdev_set_param(ar, arvif->vdev_id, vdev_param, ldpc);
	if (ret) {
		ath10k_warn(ar, "failed to set ldpc param %d: %d\n", ldpc, ret);
		return ret;
	}

	return 0;
}
