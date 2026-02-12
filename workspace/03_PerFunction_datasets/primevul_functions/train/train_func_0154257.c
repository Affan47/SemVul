static void i40e_dcb_reconfigure(struct i40e_pf *pf)
{
	u8 tc_map = 0;
	int ret;
	u8 v;


	tc_map = i40e_pf_get_tc_map(pf);
	for (v = 0; v < I40E_MAX_VEB; v++) {
		if (!pf->veb[v])
			continue;
		ret = i40e_veb_config_tc(pf->veb[v], tc_map);
		if (ret) {
			dev_info(&pf->pdev->dev,
				 "Failed configuring TC for VEB seid=%d\n",
				 pf->veb[v]->seid);

		}
	}


	for (v = 0; v < pf->num_alloc_vsi; v++) {
		if (!pf->vsi[v])
			continue;


		if (v == pf->lan_vsi)
			tc_map = i40e_pf_get_tc_map(pf);
		else
			tc_map = I40E_DEFAULT_TRAFFIC_CLASS;

		ret = i40e_vsi_config_tc(pf->vsi[v], tc_map);
		if (ret) {
			dev_info(&pf->pdev->dev,
				 "Failed configuring TC for VSI seid=%d\n",
				 pf->vsi[v]->seid);

		} else {

			i40e_vsi_map_rings_to_vectors(pf->vsi[v]);
			if (pf->vsi[v]->netdev)
				i40e_dcbnl_set_all(pf->vsi[v]);
		}
	}
}
