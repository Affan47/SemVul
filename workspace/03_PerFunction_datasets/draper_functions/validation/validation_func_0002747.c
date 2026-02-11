_set_duration (GESTimelineElement * element, GstClockTime duration)
{
  GESTrackElement *object = GES_TRACK_ELEMENT (element);
  GESTrackElementPrivate *priv = object->priv;

  if (GST_CLOCK_TIME_IS_VALID (_MAXDURATION (element)) &&
      duration > _INPOINT (object) + _MAXDURATION (element))
    duration = _MAXDURATION (element) - _INPOINT (object);

  if (priv->gnlobject != NULL) {
    if (G_UNLIKELY (duration == _DURATION (object)))
      return FALSE;

    g_object_set (priv->gnlobject, "duration", duration, NULL);
  } else
    priv->pending_duration = duration;

  _update_control_bindings (element, ges_timeline_element_get_inpoint (element),
      duration);

  return TRUE;
}
