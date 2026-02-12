int i40e_vsi_start_rings(struct i40e_vsi *vsi)
{
	int ret = 0;


	ret = i40e_vsi_control_rx(vsi, true);
	if (ret)
		return ret;
	ret = i40e_vsi_control_tx(vsi, true);

	return ret;
}
