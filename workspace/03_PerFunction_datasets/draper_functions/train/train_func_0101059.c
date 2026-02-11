fc_disc_done(struct fc_disc *disc, enum fc_disc_event event)
{
	struct fc_lport *lport = fc_disc_lport(disc);
	struct fc_rport_priv *rdata;

	FC_DISC_DBG(disc, "Discovery complete\n");

	disc->pending = 0;
	if (disc->requested) {
		fc_disc_restart(disc);
		return;
	}


	list_for_each_entry_rcu(rdata, &disc->rports, peers) {
		if (!rdata->disc_id)
			continue;
		if (rdata->disc_id == disc->disc_id)
			lport->tt.rport_login(rdata);
		else
			lport->tt.rport_logoff(rdata);
	}

	mutex_unlock(&disc->disc_mutex);
	disc->disc_callback(lport, event);
	mutex_lock(&disc->disc_mutex);
}
