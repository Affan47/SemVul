polkit_details_to_gvariant (PolkitDetails *details)
{
  GVariant *ret;
  GVariantBuilder builder;

  g_variant_builder_init (&builder, G_VARIANT_TYPE ("a{ss}"));
  if (details != NULL && details->hash != NULL)
    {
      GHashTableIter hash_iter;
      const gchar *key;
      const gchar *value;

      g_hash_table_iter_init (&hash_iter, details->hash);
      while (g_hash_table_iter_next (&hash_iter, (gpointer) &key, (gpointer) &value))
        g_variant_builder_add (&builder, "{ss}", key, value);
    }
  ret = g_variant_builder_end (&builder);
  return ret;
}
