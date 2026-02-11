get_target (gpointer data)
{
  GdkGrabStatus  status;
  GdkCursor     *cross;
  GdkWindow     *root;

  root = gdk_get_default_root_window ();

  gdk_window_add_filter (root, (GdkFilterFunc) target_filter, NULL);

  cross = gdk_cursor_new (GDK_CROSS);
  status = gdk_pointer_grab (root, FALSE, GDK_BUTTON_PRESS_MASK,
                             NULL, cross, GDK_CURRENT_TIME);
  gdk_cursor_unref (cross);

  if (status != GDK_GRAB_SUCCESS)
    {
      g_warning ("Pointer grab failed.\n");
      clean_up ();
      return FALSE;
    }

  status = gdk_keyboard_grab (root, FALSE, GDK_CURRENT_TIME);
  if (status != GDK_GRAB_SUCCESS)
    {
      g_warning ("Keyboard grab failed.\n");
      clean_up ();
      return FALSE;
    }

  gdk_flush ();

  return FALSE;
}
