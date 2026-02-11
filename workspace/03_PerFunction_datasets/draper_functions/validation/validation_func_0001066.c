make_sortkey(const gchar *name, const gint case_sensitive) {
    if (case_sensitive) {
        return g_utf8_collate_key(name, -1);
    }
    else {
        gchar *casefolded = g_utf8_casefold(name, -1);
        gchar *key = g_utf8_collate_key(casefolded, -1);
        g_free(casefolded);
        return key;
    }
}
