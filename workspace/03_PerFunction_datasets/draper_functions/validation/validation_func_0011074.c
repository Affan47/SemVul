bfa_fcs_lport_ns_sm_online(struct bfa_fcs_lport_ns_s *ns,
			enum vport_ns_event event)
{
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	switch (event) {
	case NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		break;

	case NSSM_EVENT_NS_QUERY:


		if (BFA_FCS_VPORT_IS_INITIATOR_MODE(ns->port)) {
			bfa_sm_set_state(ns,
				bfa_fcs_lport_ns_sm_sending_gid_ft);
			bfa_fcs_lport_ns_send_gid_ft(ns, NULL);
		};
		break;

	default:
		bfa_sm_fault(ns->port->fcs, event);
	}
}
