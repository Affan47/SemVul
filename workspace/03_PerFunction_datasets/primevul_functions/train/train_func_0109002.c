text_emit (int index, session *sess, char *a, char *b, char *c, char *d,
			  time_t timestamp)
{
	char *word[PDIWORDS];
	int i;
	unsigned int stripcolor_args = (chanopt_is_set (prefs.hex_text_stripcolor_msg, sess->text_strip) ? 0xFFFFFFFF : 0);
	char tbuf[NICKLEN + 4];

	if (prefs.hex_text_color_nicks && (index == XP_TE_CHANACTION || index == XP_TE_CHANMSG))
	{
		g_snprintf (tbuf, sizeof (tbuf), "\003%d%s", text_color_of (a), a);
		a = tbuf;
		stripcolor_args &= ~ARG_FLAG(1);
	}

	word[0] = te[index].name;
	word[1] = (a ? a : "\000");
	word[2] = (b ? b : "\000");
	word[3] = (c ? c : "\000");
	word[4] = (d ? d : "\000");
	for (i = 5; i < PDIWORDS; i++)
		word[i] = "\000";

	if (plugin_emit_print (sess, word, timestamp))
		return;


	if (!is_session (sess))
		return;

	switch (index)
	{
	case XP_TE_JOIN:
	case XP_TE_PART:
	case XP_TE_PARTREASON:
	case XP_TE_QUIT:

		if (chanopt_is_set (prefs.hex_irc_conf_mode, sess->text_hidejoinpart))
			return;
		break;


	case XP_TE_PRIVMSG:
	case XP_TE_DPRIVMSG:
	case XP_TE_PRIVACTION:
	case XP_TE_DPRIVACTION:
		if (chanopt_is_set (prefs.hex_input_beep_priv, sess->alert_beep) && (!prefs.hex_away_omit_alerts || !sess->server->is_away))
			sound_beep (sess);
		if (chanopt_is_set (prefs.hex_input_flash_priv, sess->alert_taskbar) && (!prefs.hex_away_omit_alerts || !sess->server->is_away))
			fe_flash_window (sess);

		if (sess->alert_tray == SET_ON)
			fe_tray_set_icon (FE_ICON_MESSAGE);
		break;


	case XP_TE_HCHANACTION:
	case XP_TE_HCHANMSG:
		fe_set_tab_color (sess, 3);
		if (chanopt_is_set (prefs.hex_input_beep_hilight, sess->alert_beep) && (!prefs.hex_away_omit_alerts || !sess->server->is_away))
			sound_beep (sess);
		if (chanopt_is_set (prefs.hex_input_flash_hilight, sess->alert_taskbar) && (!prefs.hex_away_omit_alerts || !sess->server->is_away))
			fe_flash_window (sess);
		if (sess->alert_tray == SET_ON)
			fe_tray_set_icon (FE_ICON_MESSAGE);
		break;


	case XP_TE_CHANACTION:
	case XP_TE_CHANMSG:
		if (chanopt_is_set (prefs.hex_input_beep_chans, sess->alert_beep) && (!prefs.hex_away_omit_alerts || !sess->server->is_away))
			sound_beep (sess);
		if (chanopt_is_set (prefs.hex_input_flash_chans, sess->alert_taskbar) && (!prefs.hex_away_omit_alerts || !sess->server->is_away))
			fe_flash_window (sess);
		if (sess->alert_tray == SET_ON)
			fe_tray_set_icon (FE_ICON_MESSAGE);
		break;


	case XP_TE_CHANGENICK:
		if (prefs.hex_irc_hide_nickchange)
			return;
		break;
	}

	sound_play_event (index);
	display_event (sess, index, word, stripcolor_args, timestamp);
}
