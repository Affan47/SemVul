bfa_fcs_vport_delete(struct bfa_fcs_vport_s *vport)
{

	if (vport->lport.port_cfg.preboot_vp)
		return BFA_STATUS_PBC;

	bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_DELETE);

	return BFA_STATUS_OK;
}
