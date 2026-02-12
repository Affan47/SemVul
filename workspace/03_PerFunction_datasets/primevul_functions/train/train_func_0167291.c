theme_adium_focus_toggled (EmpathyChatView *view,
			   gboolean         has_focus)
{
	EmpathyThemeAdiumPriv *priv = GET_PRIV (view);

	priv->has_focus = has_focus;
	if (!priv->has_focus) {


		g_queue_foreach (&priv->acked_messages,
				 theme_adium_remove_acked_message_unread_mark_foreach,
				 view);
		g_queue_clear (&priv->acked_messages);

		priv->has_unread_message = FALSE;
	}
}
