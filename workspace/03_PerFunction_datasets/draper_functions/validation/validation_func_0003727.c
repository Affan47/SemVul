send_msg(struct ha_msg* msg, lrmd_client_t* client)
{
	if (!client) {
		lrmd_log(LOG_WARNING,
			"%s: zero client", __FUNCTION__);
		return;
	}
	if (HA_OK != ha_msg_mod(msg,F_LRM_APP,client->app_name)) {
		lrmd_log(LOG_ERR,"%s:%d: cannot add field to a message"
		,	__FUNCTION__, __LINE__);
		return;
	}
	send_cbk_msg(msg, client);
}
