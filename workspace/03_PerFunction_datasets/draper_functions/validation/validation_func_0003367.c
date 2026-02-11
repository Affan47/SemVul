gtCSVAccess( const char * pszFilename )

{
    CSVTable    *psTable;
    FILE        *fp;

    if( pszFilename == NULL )
        return NULL;


    for( psTable = psCSVTableList; psTable != NULL; psTable = psTable->psNext )
    {
        if( EQUAL(psTable->pszFilename,pszFilename) )
        {


            return( psTable );
        }
    }


    fp = VSIFOpen( pszFilename, "rb" );
    if( fp == NULL )
        return NULL;


    psTable = (CSVTable *) CPLCalloc(sizeof(CSVTable),1);

    psTable->fp = fp;
    psTable->pszFilename = CPLStrdup( pszFilename );
    psTable->psNext = psCSVTableList;

    psCSVTableList = psTable;


    psTable->papszFieldNames = CSVReadParseLine( fp );

    return( psTable );
}
