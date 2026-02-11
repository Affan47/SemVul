clutter_event_set_source (ClutterEvent *event,
                          ClutterActor *actor)
{
  g_return_if_fail (event != NULL);
  g_return_if_fail (actor == NULL || CLUTTER_IS_ACTOR (actor));

  event->any.source = actor;
}
