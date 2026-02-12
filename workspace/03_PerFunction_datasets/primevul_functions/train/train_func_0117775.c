pk_transaction_set_session_state (PkTransaction *transaction,
				  GError **error)
{
	gboolean ret;
	g_autofree gchar *session = NULL;
	g_autofree gchar *proxy_http = NULL;
	g_autofree gchar *proxy_https = NULL;
	g_autofree gchar *proxy_ftp = NULL;
	g_autofree gchar *proxy_socks = NULL;
	g_autofree gchar *no_proxy = NULL;
	g_autofree gchar *pac = NULL;
	g_autofree gchar *cmdline = NULL;
	PkTransactionPrivate *priv = transaction->priv;


	session = pk_dbus_get_session (priv->dbus, priv->sender);
	if (session == NULL) {
		g_set_error_literal (error, 1, 0, "failed to get the session");
		return FALSE;
	}


	ret = pk_transaction_db_get_proxy (priv->transaction_db,
					   priv->uid,
					   session,
					   &proxy_http,
					   &proxy_https,
					   &proxy_ftp,
					   &proxy_socks,
					   &no_proxy,
					   &pac);
	if (!ret) {
		g_set_error_literal (error, 1, 0,
				     "failed to get the proxy from the database");
		return FALSE;
	}


	pk_backend_job_set_proxy (priv->job,
				  proxy_http,
				  proxy_https,
				  proxy_ftp,
				  proxy_socks,
				  no_proxy,
				  pac);


	cmdline = g_strdup_printf ("PackageKit: %s",
				   pk_role_enum_to_string (priv->role));
	pk_backend_job_set_uid (priv->job, priv->uid);
	pk_backend_job_set_cmdline (priv->job, cmdline);
	return TRUE;
}
