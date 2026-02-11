close_button_clicked_cb (GtkWidget *tab_label,
                         GtkWidget *screen_container)
{
  GtkWidget *toplevel;
  TerminalWindow *window;
  TerminalWindowPrivate *priv;
  TerminalScreen *screen;

  toplevel = gtk_widget_get_toplevel (screen_container);
  if (!gtk_widget_is_toplevel (toplevel))
    return;

  if (!TERMINAL_IS_WINDOW (toplevel))
    return;

  window = TERMINAL_WINDOW (toplevel);
  priv = window->priv;

  screen = terminal_screen_container_get_screen (TERMINAL_SCREEN_CONTAINER (screen_container));
  if (confirm_close_window_or_tab (window, screen))
    return;

  terminal_window_remove_screen (window, screen);
}
