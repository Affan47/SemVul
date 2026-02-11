st_widget_leave (ClutterActor         *actor,
                 ClutterCrossingEvent *event)
{
  StWidgetPrivate *priv = ST_WIDGET (actor)->priv;

  if (priv->track_hover)
    {
      if (!event->related || !clutter_actor_contains (actor, event->related))
        st_widget_set_hover (ST_WIDGET (actor), FALSE);
    }

  if (CLUTTER_ACTOR_CLASS (st_widget_parent_class)->leave_event)
    return CLUTTER_ACTOR_CLASS (st_widget_parent_class)->leave_event (actor, event);
  else
    return FALSE;
}
