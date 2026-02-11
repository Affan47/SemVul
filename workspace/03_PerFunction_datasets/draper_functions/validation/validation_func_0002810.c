Create (
    const char *pszFilename,
    char **papszOptions )
{

    int bResult = FALSE;

    if (strcmp(pszFilename, "/dev/stdout") == 0)
        pszFilename = "/vsistdout/";

    pszName = CPLStrdup ( pszFilename );
    bUpdate = TRUE;


    if ( strcmp(pszFilename, "/vsistdout/") == 0 ||
         strncmp(pszFilename, "/vsigzip/", 9) == 0 ||
         EQUAL ( CPLGetExtension ( pszFilename ), "kml" ) )
        bResult = CreateKml ( pszFilename, papszOptions );


    else if ( EQUAL ( CPLGetExtension ( pszFilename ), "kmz" ) )
        bResult = CreateKmz ( pszFilename, papszOptions );


    else
        bResult = CreateDir ( pszFilename, papszOptions );

    return bResult;
}
