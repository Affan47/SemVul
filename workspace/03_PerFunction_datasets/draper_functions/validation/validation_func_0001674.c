cg_combo_flags_window_key_press_cb (G_GNUC_UNUSED GtkWidget *widget,
                                    GdkEventKey *event,
                                    gpointer data)
{
	CgComboFlags *combo;
	CgComboFlagsPrivate *priv;

	combo = CG_COMBO_FLAGS (data);
	priv = CG_COMBO_FLAGS_PRIVATE (combo);

	switch (event->keyval)
	{
	case GDK_KEY_Escape:
		priv->editing_canceled = TRUE;
		cg_combo_flags_popdown (combo);
		return TRUE;
		break;
	default:
		return FALSE;
		break;
	}
}
