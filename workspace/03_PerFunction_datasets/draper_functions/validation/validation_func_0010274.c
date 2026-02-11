gnc_html_register_urltype( URLType type, const char *protocol )
{
    URLType  lc_type  = NULL;
    char    *lc_proto = NULL;

    if (!gnc_html_type_to_proto_hash)
    {
        gnc_html_type_to_proto_hash = g_hash_table_new (g_str_hash, g_str_equal);
        gnc_html_proto_to_type_hash = g_hash_table_new (g_str_hash, g_str_equal);
    }
    if (!protocol) return FALSE;

    lc_type = g_ascii_strdown (type, -1);
    if (g_hash_table_lookup (gnc_html_type_to_proto_hash, lc_type))
    {
        g_free (lc_type);
        return FALSE;
    }

    lc_proto = g_ascii_strdown (protocol, -1);
    g_hash_table_insert (gnc_html_type_to_proto_hash, lc_type, (gpointer)lc_proto);
    if (*lc_proto)
        g_hash_table_insert (gnc_html_proto_to_type_hash, (gpointer)lc_proto, lc_type);

    return TRUE;
}
