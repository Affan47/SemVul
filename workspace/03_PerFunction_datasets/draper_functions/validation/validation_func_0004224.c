cally_texture_new (ClutterActor *actor)
{
  GObject   *object     = NULL;
  AtkObject *accessible = NULL;

  g_return_val_if_fail (CLUTTER_IS_TEXTURE (actor), NULL);

  object = g_object_new (CALLY_TYPE_TEXTURE, NULL);

  accessible = ATK_OBJECT (object);
  atk_object_initialize (accessible, actor);

  return accessible;
}
