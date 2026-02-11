gsb_string_remplace_string ( gchar *str, gchar *old_str, gchar *new_str )
{
    gchar *ptr_debut;
    gint long_old, str_len;
    gchar *chaine, *ret, *tail;

    ptr_debut = g_strstr_len ( str, -1, old_str);
    if ( ptr_debut == NULL )
        return g_strdup ( str );

    str_len = strlen ( str );
    long_old = strlen ( old_str );

    chaine = g_strndup ( str, (ptr_debut - str) );

    tail = ptr_debut + long_old;
    if ( tail >= str + str_len )
        ret = g_strconcat ( chaine, new_str, NULL );
    else
        ret = g_strconcat ( chaine, new_str, tail, NULL );

    g_free ( chaine );

    return ret;
}
