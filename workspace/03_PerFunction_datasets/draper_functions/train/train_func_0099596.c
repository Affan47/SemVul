wnck_window_unmaximize              (WnckWindow *window)
{
  g_return_if_fail (WNCK_IS_WINDOW (window));

  _wnck_change_state (WNCK_SCREEN_XSCREEN (window->priv->screen),
		      window->priv->xwindow,
                      FALSE,
                      _wnck_atom_get ("_NET_WM_STATE_MAXIMIZED_VERT"),
                      _wnck_atom_get ("_NET_WM_STATE_MAXIMIZED_HORZ"));
}
