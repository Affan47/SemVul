gsb_date_set_format_date ( const gchar *format_date )
{
    if ( format && strlen ( format ) )
        g_free ( format );

    if ( format_date == NULL )
        format = NULL;
    else if ( strcmp ( format_date, "%d/%m/%Y" ) == 0 )
        format = g_strdup ( "%d/%m/%Y" );
    else if ( strcmp ( format_date, "%m/%d/%Y" ) == 0 )
        format = g_strdup ( "%m/%d/%Y" );
    else
        format = NULL;

    if ( last_date )
        g_free ( last_date );
    last_date = NULL;
}
