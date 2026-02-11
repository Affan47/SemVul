strip_whitespace (gchar **original)
{
    GString *reassembled;
    gchar **split;
    const gchar *str;
    gint idx, n_stripped;
    size_t len;

    split = g_strsplit (*original, "\n", -1);
    reassembled = g_string_new (NULL);
    n_stripped = 0;

    for (idx = 0; split[idx] != NULL; idx++) {
        str = split[idx];

        len = strspn (str, WHITESPACE_CHARS);
        if (len)
            str += len;

        if (strlen (str) == 0 &&
            ((split[idx + 1] == NULL) || strlen (split[idx + 1]) == 0))
            continue;

        if (n_stripped++ > 0)
            g_string_append (reassembled, "\n");
        g_string_append (reassembled, str);
    }

    g_strfreev (split);
    g_free (*original);

    *original = g_string_free (reassembled, FALSE);
}
