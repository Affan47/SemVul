int i40e_is_vsi_uplink_mode_veb(struct i40e_vsi *vsi)
{
	struct i40e_veb *veb;
	struct i40e_pf *pf = vsi->back;


	if (vsi->veb_idx >= I40E_MAX_VEB)
		return 1;

	veb = pf->veb[vsi->veb_idx];
	if (!veb) {
		dev_info(&pf->pdev->dev,
			 "There is no veb associated with the bridge\n");
		return -ENOENT;
	}


	if (veb->bridge_mode & BRIDGE_MODE_VEPA) {
		return 0;
	} else {

		return 1;
	}


	return 0;
}
