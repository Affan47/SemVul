connect_mcl_event_cb(GIOChannel *chan, GError *gerr,
							gpointer user_data)
{
	struct mcap_instance *mi = user_data;
	struct mcap_mcl *mcl;
	bdaddr_t dst;
	char address[18], srcstr[18];
	GError *err = NULL;

	if (gerr)
		return;

	bt_io_get(chan, BT_IO_L2CAP, &err,
			BT_IO_OPT_DEST_BDADDR, &dst,
			BT_IO_OPT_DEST, address,
			BT_IO_OPT_INVALID);
	if (err) {
		error("%s", err->message);
		g_error_free(err);
		goto drop;
	}

	ba2str(&mi->src, srcstr);
	mcl = find_mcl(mi->mcls, &dst);
	if (mcl) {
		error("Control channel already created with %s on adapter %s",
				address, srcstr);
		goto drop;
	}

	mcl = find_mcl(mi->cached, &dst);
	if (!mcl) {
		mcl = g_new0(struct mcap_mcl, 1);
		mcl->mi = mcap_instance_ref(mi);
		bacpy(&mcl->addr, &dst);
		set_default_cb(mcl);
		mcl->next_mdl = (rand() % MCAP_MDLID_FINAL) + 1;
	}

	set_mcl_conf(chan, mcl);

	return;
drop:
	g_io_channel_shutdown(chan, TRUE, NULL);
}
