fc_rport_enter_adisc(struct fc_rport_priv *rdata)
{
	struct fc_lport *lport = rdata->local_port;
	struct fc_frame *fp;

	FC_RPORT_DBG(rdata, "sending ADISC from %s state\n",
		     fc_rport_state(rdata));

	fc_rport_state_enter(rdata, RPORT_ST_ADISC);

	fp = fc_frame_alloc(lport, sizeof(struct fc_els_adisc));
	if (!fp) {
		fc_rport_error_retry(rdata, fp);
		return;
	}
	if (!lport->tt.elsct_send(lport, rdata->ids.port_id, fp, ELS_ADISC,
				  fc_rport_adisc_resp, rdata,
				  2 * lport->r_a_tov))
		fc_rport_error_retry(rdata, NULL);
	else
		kref_get(&rdata->kref);
}
