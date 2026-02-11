dbus_g_type_get_struct (const char *container,
                        GType first_type,
                        ...)
{
  GArray *types;
  GType curtype, ret;
  va_list args;
  va_start (args, first_type);

  types = g_array_new (FALSE, FALSE, sizeof (GType));
  curtype = first_type;
  while (curtype != G_TYPE_INVALID)
    {
      g_array_append_val (types, curtype);
      curtype = va_arg (args, GType);
    }
  va_end (args);

  ret = lookup_or_register_specialized (container, types->len,
      (GType *) types->data);

  g_array_free (types, TRUE);

  return ret;
}
