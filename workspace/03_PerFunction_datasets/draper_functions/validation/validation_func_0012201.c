unique_imported_name ( gchar * account_name )
{
    GSList *tmp_list;
    gchar *basename;
    gint iter = 1;

    tmp_list = liste_comptes_importes;
    basename = my_strdup ( account_name );
    if ( !liste_comptes_importes )
        return basename;

    do
    {
        struct struct_compte_importation *tmp_account;

        tmp_account = (struct struct_compte_importation *) tmp_list -> data;

        if ( tmp_account -> nom_de_compte == NULL )
            tmp_account -> nom_de_compte = g_strdup ( basename );

        if ( !strcmp ( basename, tmp_account -> nom_de_compte ) )
        {
            tmp_list = liste_comptes_importes;

            g_free (basename);
            basename = g_strdup_printf ( _("%s #%d"), account_name, ++iter );
        }
        else
            tmp_list = tmp_list -> next;
    }
    while ( tmp_list );

    return basename;
}
