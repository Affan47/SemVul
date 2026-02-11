save_prefs_file(
        gms_private_t *this
    )
{
    GString *gms_pref = g_string_new("");

    g_string_printf(gms_pref , "%s/plugins", this->config_dir );

    if ( g_file_test( this->config_dir, G_FILE_TEST_EXISTS ) != TRUE )
        g_mkdir( this->config_dir, 0755 ) ;

    if ( g_file_test( gms_pref->str, G_FILE_TEST_EXISTS ) != TRUE )
        g_mkdir( gms_pref->str, 0755 ) ;

    if ( g_file_test( gms_pref->str, G_FILE_TEST_IS_DIR ) == TRUE )
    {
        FILE *fd ;
        g_string_append_c( gms_pref, '/' );
        g_string_append( gms_pref, pref_filename );

        fd = g_fopen( gms_pref->str, "w" ) ;
        if ( fd != NULL )
        {
            int  ii ;
            for ( ii = 0 ; ii <GMS_NB_TYPE_SCRIPT ;ii++ )
                fprintf(fd,"# %s\n%s\n",label_script_cmd[ii],this->script_cmd[ii]->str);

            fclose(fd) ;
        }
    }
    g_string_free( gms_pref , TRUE) ;
}
