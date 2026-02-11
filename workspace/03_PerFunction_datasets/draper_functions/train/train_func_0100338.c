CreateDataSource( const char * pszName,
                                               char **papszOptions )

{
    OGRILI1DataSource    *poDS = new OGRILI1DataSource();

    if( !poDS->Create( pszName, papszOptions ) )
    {
        delete poDS;
        return NULL;
    }
    else
        return poDS;
}
