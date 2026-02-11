mcap_connect_mdl(struct mcap_mdl *mdl, uint8_t mode,
					uint16_t dcpsm,
					mcap_mdl_operation_cb connect_cb,
					gpointer user_data,
					GDestroyNotify destroy,
					GError **err)
{
	struct mcap_mdl_op_cb *con;

	if (mdl->state != MDL_WAITING) {
		g_set_error(err, MCAP_ERROR, MCAP_ERROR_INVALID_MDL,
					"%s", error2str(MCAP_INVALID_MDL));
		return FALSE;
	}

	if ((mode != L2CAP_MODE_ERTM) && (mode != L2CAP_MODE_STREAMING)) {
		g_set_error(err, MCAP_ERROR, MCAP_ERROR_INVALID_ARGS,
						"Invalid MDL configuration");
		return FALSE;
	}

	con = g_new0(struct mcap_mdl_op_cb, 1);
	con->mdl = mcap_mdl_ref(mdl);
	con->cb.op = connect_cb;
	con->destroy = destroy;
	con->user_data = user_data;

	mdl->dc = bt_io_connect(BT_IO_L2CAP, mcap_connect_mdl_cb, con,
				(GDestroyNotify) free_mcap_mdl_op, err,
				BT_IO_OPT_SOURCE_BDADDR, &mdl->mcl->mi->src,
				BT_IO_OPT_DEST_BDADDR, &mdl->mcl->addr,
				BT_IO_OPT_PSM, dcpsm,
				BT_IO_OPT_MTU, MCAP_DC_MTU,
				BT_IO_OPT_SEC_LEVEL, mdl->mcl->mi->sec,
				BT_IO_OPT_MODE, mode,
				BT_IO_OPT_INVALID);
	if (!mdl->dc) {
		DBG("MDL Connection error");
		mdl->state = MDL_CLOSED;
		mcap_mdl_unref(con->mdl);
		g_free(con);
		return FALSE;
	}

	return TRUE;
}
