import_select_file ( GtkWidget * button, GtkWidget * assistant )
{
    GSList * filenames, * iterator;
    GtkTreeModel * model;

    filenames = gsb_import_create_file_chooser ( NULL, assistant );
    if (!filenames)
    return FALSE;

    iterator = filenames;

    model = g_object_get_data ( G_OBJECT ( assistant ), "model" );

    while ( iterator && model )
    {
    GtkTreeIter iter;
    const gchar *type;
    gchar *nom_fichier;
    gchar *tmp_str;
    gchar *contents;
    gchar *charmap;
    GError *error = NULL;
    gchar * extension;


    extension = strrchr ( iterator -> data, '.' );


    if ( extension && strcmp ( extension, ".gnc" ) == 0 )
        gsb_import_gunzip_file ( iterator -> data );


    if ( ! g_file_get_contents ( iterator -> data, &tmp_str, NULL, &error ) )
    {
        g_print ( _("Unable to read file: %s\n"), error -> message);
        g_error_free ( error );
        return FALSE;
    }

    type = autodetect_file_type ( iterator -> data, tmp_str );


    if ( strcmp ( type, "OFX" ) == 0 )
    {
        nom_fichier = g_strconcat (g_get_tmp_dir (),G_DIR_SEPARATOR_S,
                                   g_path_get_basename ( iterator -> data ), NULL);
        if (! gsb_import_set_tmp_file (nom_fichier, tmp_str ) )
        {
            g_free ( tmp_str );
            return FALSE;
        }
        if ( ( charmap = utils_files_get_ofx_charset ( tmp_str ) ) != NULL )
        {
            if ( charmap_imported && strlen ( charmap_imported ) > 0 )
                g_free ( charmap_imported );
            charmap_imported = charmap;
        }
    }
    else
        nom_fichier = my_strdup (iterator -> data);


    if ( ! strcmp ( type, "CSV" ) )
    {
        gsb_assistant_set_next ( assistant, IMPORT_FILESEL_PAGE, IMPORT_CSV_PAGE );
        gsb_assistant_set_prev ( assistant, IMPORT_RESUME_PAGE, IMPORT_CSV_PAGE );
    }


    contents = g_convert ( tmp_str, -1, "UTF-8", charmap_imported, NULL, NULL, NULL );

    if ( contents == NULL )
        charmap_imported = utils_files_create_sel_charset ( assistant, tmp_str,
                    charmap_imported,
                    g_path_get_basename ( iterator -> data ) );
    else
        g_free ( contents );

    gtk_tree_store_append ( GTK_TREE_STORE ( model ), &iter, NULL );
    gtk_tree_store_set ( GTK_TREE_STORE ( model ), &iter,
                        IMPORT_FILESEL_SELECTED, TRUE,
                        IMPORT_FILESEL_TYPENAME, type,
                        IMPORT_FILESEL_FILENAME, g_path_get_basename ( iterator -> data ),
                        IMPORT_FILESEL_REALNAME, nom_fichier,
                        IMPORT_FILESEL_TYPE, type,
                        IMPORT_FILESEL_CODING, charmap_imported,
                        -1 );
    g_free ( nom_fichier );
    g_free ( tmp_str );

    if ( strcmp ( type, _("Unknown") ) )
    {

        gtk_widget_set_sensitive ( g_object_get_data ( G_OBJECT (assistant), "button_next" ),
                        TRUE );
    }

    iterator = iterator -> next;
    }

    if ( filenames )
        g_slist_free ( filenames );
    return FALSE;
}
