is_depayloader (GstElementFactory *factory)
{
  const gchar *klass = gst_element_factory_get_klass (factory);
  return (klass_contains (klass, "Network") &&
          (klass_contains (klass, "Depayloader") ||
           klass_contains (klass, "Depayr")));
}
