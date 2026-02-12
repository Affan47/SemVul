bool i40e_is_vsi_in_vlan(struct i40e_vsi *vsi)
{

	if (vsi->info.pvid)
		return true;


	return vsi->has_vlan_filter;
}
