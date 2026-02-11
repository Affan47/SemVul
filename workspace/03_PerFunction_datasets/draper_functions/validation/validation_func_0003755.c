vmsg_send_qstat_answer(struct gnutella_node *n,
	const struct guid *muid, uint16 hits)
{
	uint32 msgsize;
	uint32 paysize = sizeof(uint16);
	char *payload;

	msgsize = vmsg_fill_header(v_tmp_header, paysize, sizeof v_tmp);
	gnutella_header_set_muid(v_tmp_header, muid);
	payload = vmsg_fill_type(v_tmp_data, T_BEAR, 12, 1);

	poke_le16(payload, hits);

	gmsg_ctrl_sendto_one(n, v_tmp, msgsize);

	if (GNET_PROPERTY(vmsg_debug) > 2 || GNET_PROPERTY(log_vmsg_tx)) {
		g_debug("VMSG sent %s with hits=%u to %s",
			gmsg_infostr_full(v_tmp, msgsize), hits, node_infostr(n));
	}
}
