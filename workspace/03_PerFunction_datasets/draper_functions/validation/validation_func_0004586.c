gst_child_proxy_lookup (GstChildProxy * object, const gchar * name,
    GObject ** target, GParamSpec ** pspec)
{
  GObject *obj;
  gboolean res = FALSE;
  gchar **names, **current;

  g_return_val_if_fail (GST_IS_CHILD_PROXY (object), FALSE);
  g_return_val_if_fail (name != NULL, FALSE);

  obj = g_object_ref (object);

  current = names = g_strsplit (name, "::", -1);

  while (current[1]) {
    GObject *next;

    if (!GST_IS_CHILD_PROXY (obj)) {
      GST_INFO
          ("object %s is not a parent, so you cannot request a child by name %s",
          (GST_IS_OBJECT (obj) ? GST_OBJECT_NAME (obj) : ""), current[0]);
      break;
    }
    next = gst_child_proxy_get_child_by_name (GST_CHILD_PROXY (obj),
        current[0]);
    if (!next) {
      GST_INFO ("no such object %s", current[0]);
      break;
    }
    g_object_unref (obj);
    obj = next;
    current++;
  }


  if (current[1] == NULL) {
    GParamSpec *spec =
        g_object_class_find_property (G_OBJECT_GET_CLASS (obj), current[0]);
    if (spec == NULL) {
      GST_INFO ("no param spec named %s", current[0]);
    } else {
      if (pspec)
        *pspec = spec;
      if (target) {
        g_object_ref (obj);
        *target = obj;
      }
      res = TRUE;
    }
  }
  g_object_unref (obj);
  g_strfreev (names);
  return res;
}
