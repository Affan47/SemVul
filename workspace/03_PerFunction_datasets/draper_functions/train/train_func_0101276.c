fc_rport_flogi_resp(struct fc_seq *sp, struct fc_frame *fp,
				void *rp_arg)
{
	struct fc_rport_priv *rdata = rp_arg;
	struct fc_lport *lport = rdata->local_port;
	struct fc_els_flogi *flogi;
	unsigned int r_a_tov;

	FC_RPORT_DBG(rdata, "Received a FLOGI %s\n", fc_els_resp_type(fp));

	if (fp == ERR_PTR(-FC_EX_CLOSED))
		goto put;

	mutex_lock(&rdata->rp_mutex);

	if (rdata->rp_state != RPORT_ST_FLOGI) {
		FC_RPORT_DBG(rdata, "Received a FLOGI response, but in state "
			     "%s\n", fc_rport_state(rdata));
		if (IS_ERR(fp))
			goto err;
		goto out;
	}

	if (IS_ERR(fp)) {
		fc_rport_error(rdata, fp);
		goto err;
	}

	if (fc_frame_payload_op(fp) != ELS_LS_ACC)
		goto bad;
	if (fc_rport_login_complete(rdata, fp))
		goto bad;

	flogi = fc_frame_payload_get(fp, sizeof(*flogi));
	if (!flogi)
		goto bad;
	r_a_tov = ntohl(flogi->fl_csp.sp_r_a_tov);
	if (r_a_tov > rdata->r_a_tov)
		rdata->r_a_tov = r_a_tov;

	if (rdata->ids.port_name < lport->wwpn)
		fc_rport_enter_plogi(rdata);
	else
		fc_rport_state_enter(rdata, RPORT_ST_PLOGI_WAIT);
out:
	fc_frame_free(fp);
err:
	mutex_unlock(&rdata->rp_mutex);
put:
	kref_put(&rdata->kref, rdata->local_port->tt.rport_destroy);
	return;
bad:
	FC_RPORT_DBG(rdata, "Bad FLOGI response\n");
	fc_rport_error_retry(rdata, fp);
	goto out;
}
