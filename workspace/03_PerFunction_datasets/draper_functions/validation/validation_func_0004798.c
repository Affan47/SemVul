begin_user_action_handler (GtkTextBuffer               *buffer,
                           GtkSourceUndoManagerDefault *um)
{
	if (um->priv->running_not_undoable_actions > 0)
		return;

	um->priv->actions_in_current_group = 0;
}
