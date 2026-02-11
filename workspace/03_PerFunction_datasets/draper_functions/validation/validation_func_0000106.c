handle_capture_event_cb (ClutterActor *trough,
                         ClutterEvent *event,
                         MxScrollBar  *bar)
{
  if (clutter_event_type (event) == CLUTTER_MOTION)
    {
      move_slider (bar,
                   ((ClutterMotionEvent*) event)->x,
                   ((ClutterMotionEvent*) event)->y);
    }
  else if (clutter_event_type (event) == CLUTTER_BUTTON_RELEASE
           && ((ClutterButtonEvent*) event)->button == 1)
    {
      ClutterActor *stage, *target;

      stage = clutter_actor_get_stage(bar->priv->trough);

      if (bar->priv->capture_handler)
        {
          g_signal_handler_disconnect (stage, bar->priv->capture_handler);
          bar->priv->capture_handler = 0;
        }

      clutter_set_motion_events_enabled (TRUE);
      g_signal_emit (bar, signals[SCROLL_STOP], 0);


      target = clutter_stage_get_actor_at_pos ((ClutterStage*) stage,
                                               CLUTTER_PICK_REACTIVE,
                                               ((ClutterButtonEvent*) event)->x,
                                               ((ClutterButtonEvent*) event)->y);
      if (target != bar->priv->handle)
        {
          mx_stylable_set_style_pseudo_class (MX_STYLABLE (bar->priv->handle),
                                              NULL);
        }
      else
        {

          return FALSE;
        }
    }

  return TRUE;
}
