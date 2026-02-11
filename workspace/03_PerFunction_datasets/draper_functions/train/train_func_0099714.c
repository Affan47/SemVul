clutter_input_device_sequence_grab (ClutterInputDevice   *device,
                                    ClutterEventSequence *sequence,
                                    ClutterActor         *actor)
{
  ClutterActor *grab_actor;

  g_return_if_fail (CLUTTER_IS_INPUT_DEVICE (device));
  g_return_if_fail (CLUTTER_IS_ACTOR (actor));

  if (device->sequence_grab_actors == NULL)
    {
      grab_actor = NULL;
      device->sequence_grab_actors = g_hash_table_new (NULL, NULL);
      device->inv_sequence_grab_actors = g_hash_table_new (NULL, NULL);
    }
  else
    {
      grab_actor = g_hash_table_lookup (device->sequence_grab_actors, sequence);
    }

  if (grab_actor != NULL)
    {
      g_signal_handlers_disconnect_by_func (grab_actor,
                                            G_CALLBACK (on_grab_sequence_actor_destroy),
                                            device);
      g_hash_table_remove (device->sequence_grab_actors, sequence);
      g_hash_table_remove (device->inv_sequence_grab_actors, grab_actor);
    }

  g_hash_table_insert (device->sequence_grab_actors, sequence, actor);
  g_hash_table_insert (device->inv_sequence_grab_actors, actor, sequence);
  g_signal_connect (actor,
                    "destroy",
                    G_CALLBACK (on_grab_sequence_actor_destroy),
                    device);
}
