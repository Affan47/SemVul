palette_scheme_combo_changed_cb (GtkComboBox *combo,
                                 GParamSpec *pspec,
                                 TerminalProfile *profile)
{
  int i;

  i = gtk_combo_box_get_active (GTK_COMBO_BOX (combo));

  g_signal_handlers_block_by_func (profile, G_CALLBACK (profile_colors_notify_scheme_combo_cb), combo);
  if (i < TERMINAL_PALETTE_N_BUILTINS)
    terminal_profile_set_palette_builtin (profile, i);
  else
    {

    }
  g_signal_handlers_unblock_by_func (profile, G_CALLBACK (profile_colors_notify_scheme_combo_cb), combo);
}
