bnx2fc_tgt_lookup(struct fcoe_port *port,
					     u32 port_id)
{
	struct bnx2fc_interface *interface = port->priv;
	struct bnx2fc_hba *hba = interface->hba;
	struct bnx2fc_rport *tgt;
	struct fc_rport_priv *rdata;
	int i;

	for (i = 0; i < BNX2FC_NUM_MAX_SESS; i++) {
		tgt = hba->tgt_ofld_list[i];
		if ((tgt) && (tgt->port == port)) {
			rdata = tgt->rdata;
			if (rdata->ids.port_id == port_id) {
				if (rdata->rp_state != RPORT_ST_DELETE) {
					BNX2FC_TGT_DBG(tgt, "rport "
						"obtained\n");
					return tgt;
				} else {
					BNX2FC_TGT_DBG(tgt, "rport 0x%x "
						"is in DELETED state\n",
						rdata->ids.port_id);
					return NULL;
				}
			}
		}
	}
	return NULL;
}
