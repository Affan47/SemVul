clutter_stage_gdk_set_cursor_visible (ClutterStageWindow *stage_window,
                                      gboolean            cursor_visible)
{
  ClutterStageGdk *stage_gdk = CLUTTER_STAGE_GDK (stage_window);

  if (stage_gdk->window == NULL)
    return;

  if (cursor_visible)
    {
      gdk_window_set_cursor (stage_gdk->window, NULL);
    }
  else
    {
      if (stage_gdk->blank_cursor == NULL)
	stage_gdk->blank_cursor = gdk_cursor_new (GDK_BLANK_CURSOR);

      gdk_window_set_cursor (stage_gdk->window, stage_gdk->blank_cursor);
    }
}
