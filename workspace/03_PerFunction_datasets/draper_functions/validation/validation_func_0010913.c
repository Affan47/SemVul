Read( const char * pszFilename )

{
    DDFModule   oIREFFile;
    DDFRecord   *poRecord;


    if( !oIREFFile.Open( pszFilename ) )
        return FALSE;


    poRecord = oIREFFile.ReadRecord();
    if( poRecord == NULL )
        return FALSE;

    if( poRecord->GetStringSubfield( "IREF", 0, "MODN", 0 ) == NULL )
        return FALSE;


    CPLFree( pszXAxisName );
    pszXAxisName = CPLStrdup( poRecord->GetStringSubfield( "IREF", 0,
                                                           "XLBL", 0 ) );
    CPLFree( pszYAxisName );
    pszYAxisName = CPLStrdup( poRecord->GetStringSubfield( "IREF", 0,
                                                           "YLBL", 0 ) );


    CPLFree( pszCoordinateFormat );
    pszCoordinateFormat =
        CPLStrdup( poRecord->GetStringSubfield( "IREF", 0, "HFMT", 0 ) );


    dfXScale = poRecord->GetFloatSubfield( "IREF", 0, "SFAX", 0 );
    dfYScale = poRecord->GetFloatSubfield( "IREF", 0, "SFAY", 0 );

    dfXOffset = poRecord->GetFloatSubfield( "IREF", 0, "XORG", 0 );
    dfYOffset = poRecord->GetFloatSubfield( "IREF", 0, "YORG", 0 );

    dfXRes = poRecord->GetFloatSubfield( "IREF", 0, "XHRS", 0 );
    dfYRes = poRecord->GetFloatSubfield( "IREF", 0, "YHRS", 0 );

    nDefaultSADRFormat = EQUAL(pszCoordinateFormat,"BI32");

    return TRUE;
}
