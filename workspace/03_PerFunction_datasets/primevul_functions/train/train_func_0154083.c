void i40e_vsi_stop_rings(struct i40e_vsi *vsi)
{

	if (test_bit(__I40E_PORT_SUSPENDED, vsi->back->state))
		return i40e_vsi_stop_rings_no_wait(vsi);


	i40e_vsi_control_tx(vsi, false);
	i40e_vsi_control_rx(vsi, false);
}
