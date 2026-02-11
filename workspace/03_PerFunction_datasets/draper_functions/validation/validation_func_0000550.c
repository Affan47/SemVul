brasero_session_cfg_track_removed (BraseroBurnSession *session,
				   BraseroTrack *track,
				   guint former_position)
{
	BraseroSessionCfgPrivate *priv;

	if (!brasero_session_cfg_can_update (BRASERO_SESSION_CFG (session)))
		return;

	priv = BRASERO_SESSION_CFG_PRIVATE (session);
	priv->session_blocks = 0;
	priv->session_size = 0;


	g_signal_handlers_disconnect_by_func (track,
					      brasero_session_cfg_session_loaded,
					      session);


	brasero_session_cfg_update (BRASERO_SESSION_CFG (session));
}
