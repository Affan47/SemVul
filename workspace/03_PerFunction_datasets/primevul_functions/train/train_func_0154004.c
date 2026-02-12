int i40e_vsi_add_vlan(struct i40e_vsi *vsi, u16 vid)
{
	int err;

	if (vsi->info.pvid)
		return -EINVAL;


	if (!vid)
		return 0;


	spin_lock_bh(&vsi->mac_filter_hash_lock);
	err = i40e_add_vlan_all_mac(vsi, vid);
	spin_unlock_bh(&vsi->mac_filter_hash_lock);
	if (err)
		return err;


	i40e_service_event_schedule(vsi->back);
	return 0;
}
