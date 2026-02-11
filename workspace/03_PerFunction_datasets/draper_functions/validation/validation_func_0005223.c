lowercase_value(G_GNUC_UNUSED const GwyTextHeaderContext *context,
                GHashTable *hash,
                gchar *key,
                gchar *value,
                G_GNUC_UNUSED gpointer user_data,
                G_GNUC_UNUSED GError **error)
{
    gchar *p;

    for (p = value; *p; p++)
        *p = g_ascii_tolower(*p);
    g_hash_table_replace(hash, key, value);

    return TRUE;
}
