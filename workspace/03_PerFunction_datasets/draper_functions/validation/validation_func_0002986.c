gegl_operation_set_key (const gchar *operation_name,
                        const gchar *key_name,
                        const gchar *key_value)
{
  GType         type;
  GObjectClass *klass;
  type = gegl_operation_gtype_from_name (operation_name);
  if (!type)
    return;
  klass  = g_type_class_ref (type);
  gegl_operation_class_set_key (GEGL_OPERATION_CLASS (klass), key_name, key_value);
  g_type_class_unref (klass);
}
