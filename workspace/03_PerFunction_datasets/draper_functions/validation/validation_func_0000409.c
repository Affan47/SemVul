clutter_text_release (ClutterActor *actor,
                      ClutterEvent *event)
{
  ClutterText *self = CLUTTER_TEXT (actor);
  ClutterTextPrivate *priv = self->priv;
  ClutterEventType type = clutter_event_type (event);

  if (priv->in_select_drag)
    {
      if (type == CLUTTER_BUTTON_RELEASE)
        {
          if (!priv->in_select_touch)
            {
              clutter_ungrab_pointer ();
              priv->in_select_drag = FALSE;

              return CLUTTER_EVENT_STOP;
            }
        }
      else
        {
          if (priv->in_select_touch)
            {
              ClutterInputDevice *device = clutter_event_get_device (event);
              ClutterEventSequence *sequence =
                clutter_event_get_event_sequence (event);

              clutter_input_device_sequence_ungrab (device, sequence);
              priv->in_select_touch = FALSE;
              priv->in_select_drag = FALSE;

              return CLUTTER_EVENT_STOP;
            }
        }
    }

  return CLUTTER_EVENT_PROPAGATE;
}
