mx_toggle_handle_motion_event (ClutterActor       *actor,
                               ClutterMotionEvent *event,
                               MxToggle           *toggle)
{
  MxTogglePrivate *priv = toggle->priv;

  if (mx_widget_get_disabled (MX_WIDGET (toggle)))
    return FALSE;


  if (priv->drag_offset > -1)
    {
      if (priv->slide_length)
        {
          gfloat pos, x;

          clutter_actor_transform_stage_point (CLUTTER_ACTOR (toggle),
                                               event->x,
                                               event->y,
                                               &x,
                                               NULL);

          if (priv->active)
            pos = 1 - ((priv->drag_offset - x) / priv->slide_length);
          else
            pos = (x - priv->drag_offset) / priv->slide_length;

          if (pos - priv->position)
            priv->last_move = (pos - priv->position);

          priv->position = CLAMP (pos, 0, 1);
        }
      else
        priv->position = 0;

      clutter_actor_queue_relayout (actor);
    }

  return TRUE;
}
