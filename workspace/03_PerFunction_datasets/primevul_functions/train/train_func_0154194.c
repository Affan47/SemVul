bool i40e_set_ntuple(struct i40e_pf *pf, netdev_features_t features)
{
	bool need_reset = false;


	if (features & NETIF_F_NTUPLE) {

		if (!(pf->flags & I40E_FLAG_FD_SB_ENABLED))
			need_reset = true;


		if (pf->num_fdsb_msix > 0 && !pf->num_cloud_filters) {
			pf->flags |= I40E_FLAG_FD_SB_ENABLED;
			pf->flags &= ~I40E_FLAG_FD_SB_INACTIVE;
		}
	} else {

		if (pf->flags & I40E_FLAG_FD_SB_ENABLED) {
			need_reset = true;
			i40e_fdir_filter_exit(pf);
		}
		pf->flags &= ~I40E_FLAG_FD_SB_ENABLED;
		clear_bit(__I40E_FD_SB_AUTO_DISABLED, pf->state);
		pf->flags |= I40E_FLAG_FD_SB_INACTIVE;


		pf->fd_add_err = 0;
		pf->fd_atr_cnt = 0;

		if (test_and_clear_bit(__I40E_FD_ATR_AUTO_DISABLED, pf->state))
			if ((pf->flags & I40E_FLAG_FD_ATR_ENABLED) &&
			    (I40E_DEBUG_FD & pf->hw.debug_mask))
				dev_info(&pf->pdev->dev, "ATR re-enabled.\n");
	}
	return need_reset;
}
