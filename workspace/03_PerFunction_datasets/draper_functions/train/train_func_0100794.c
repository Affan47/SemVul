atk_registry_new (void)
{
  GObject *object;

  object = g_object_new (ATK_TYPE_REGISTRY, NULL);

  g_return_val_if_fail (ATK_IS_REGISTRY (object), NULL);

  return (AtkRegistry *) object;
}
