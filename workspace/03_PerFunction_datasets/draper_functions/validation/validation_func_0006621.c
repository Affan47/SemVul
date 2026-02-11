wnck_screen_get_for_root (gulong root_window_id)
{
  int i;
  Display *display;

  if (screens == NULL)
    return NULL;

  i = 0;
  display = _wnck_get_default_display ();

  while (i < ScreenCount (display))
    {
      if (screens[i] != NULL && screens[i]->priv->xroot == root_window_id)
        return screens[i];

      ++i;
    }

  return NULL;
}
