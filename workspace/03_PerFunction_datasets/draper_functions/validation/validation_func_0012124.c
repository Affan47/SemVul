gm_mcp_vmoo_userlist_handle_set(GmMcpVmooUserlist *package, MOOVar *v) {
	MOOVar *ui;

	if (v->type != LIST) {
		return;
	}

	package->priv->initializing = TRUE;
	gm_mcp_vmoo_userlist_remove_users(package);

	for (ui = v->list; ui; ui = ui->next) {
		if (ui->type != LIST) {
			return;
		}

		gm_mcp_vmoo_userlist_handle_user_update(package, ui->list);
	}

	package->priv->initializing = FALSE;
}
