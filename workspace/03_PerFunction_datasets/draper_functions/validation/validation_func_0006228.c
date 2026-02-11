actor_remove_all (TestConformSimpleFixture *fixture,
                  gconstpointer dummy)
{
  ClutterActor *actor = clutter_actor_new ();

  g_object_ref_sink (actor);
  g_object_add_weak_pointer (G_OBJECT (actor), (gpointer *) &actor);

  clutter_actor_add_child (actor, g_object_new (CLUTTER_TYPE_ACTOR,
                                                "name", "foo",
                                                NULL));
  clutter_actor_add_child (actor, g_object_new (CLUTTER_TYPE_ACTOR,
                                                "name", "bar",
                                                NULL));
  clutter_actor_add_child (actor, g_object_new (CLUTTER_TYPE_ACTOR,
                                                "name", "baz",
                                                NULL));

  g_assert_cmpint (clutter_actor_get_n_children (actor), ==, 3);

  clutter_actor_remove_all_children (actor);

  g_assert_cmpint (clutter_actor_get_n_children (actor), ==, 0);

  clutter_actor_destroy (actor);
  g_assert (actor == NULL);
}
