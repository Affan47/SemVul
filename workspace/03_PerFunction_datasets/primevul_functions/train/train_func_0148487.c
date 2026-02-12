vpnc_watch_cb (GPid pid, gint status, gpointer user_data)
{
	NMVPNCPlugin *plugin = NM_VPNC_PLUGIN (user_data);
	NMVPNCPluginPrivate *priv = NM_VPNC_PLUGIN_GET_PRIVATE (plugin);
	guint error = 0;

	if (WIFEXITED (status)) {
		error = WEXITSTATUS (status);
		if (error != 0)
			_LOGW ("vpnc exited with error code %d", error);
	} else if (WIFSTOPPED (status))
		_LOGW ("vpnc stopped unexpectedly with signal %d", WSTOPSIG (status));
	else if (WIFSIGNALED (status))
		_LOGW ("vpnc died with signal %d", WTERMSIG (status));
	else
		_LOGW ("vpnc died from an unknown cause");

	priv->watch_id = 0;


	if (priv->out.channel)
		pipe_echo_finish (&priv->out);
	if (priv->err.channel)
		pipe_echo_finish (&priv->err);

	vpnc_cleanup (plugin, FALSE);
	remove_pidfile (plugin);


	switch (error) {
	case 2:

		nm_vpn_service_plugin_failure (NM_VPN_SERVICE_PLUGIN (plugin), NM_VPN_PLUGIN_FAILURE_LOGIN_FAILED);
		break;
	case 1:

		nm_vpn_service_plugin_failure (NM_VPN_SERVICE_PLUGIN (plugin), NM_VPN_PLUGIN_FAILURE_CONNECT_FAILED);
		break;
	default:
		nm_vpn_service_plugin_disconnect (NM_VPN_SERVICE_PLUGIN (plugin), NULL);
		break;
	}
}
