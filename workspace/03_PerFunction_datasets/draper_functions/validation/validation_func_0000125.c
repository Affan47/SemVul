atk_no_op_object_factory_new (void)
{
  GObject *factory;

  factory = g_object_new (ATK_TYPE_NO_OP_OBJECT_FACTORY, NULL);

  g_return_val_if_fail (factory != NULL, NULL);
  return ATK_OBJECT_FACTORY (factory);
}
