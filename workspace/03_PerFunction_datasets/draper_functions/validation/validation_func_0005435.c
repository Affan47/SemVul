DumpReadable( FILE * fpOut, char** papszOptions )

{
    if( fpOut == NULL )
        fpOut = stdout;

    fprintf( fpOut, "OGRFeature(%s):%ld\n", poDefn->GetName(), GetFID() );

    const char* pszDisplayFields =
            CSLFetchNameValue(papszOptions, "DISPLAY_FIELDS");
    if (pszDisplayFields == NULL || CSLTestBoolean(pszDisplayFields))
    {
        for( int iField = 0; iField < GetFieldCount(); iField++ )
        {
            OGRFieldDefn    *poFDefn = poDefn->GetFieldDefn(iField);

            fprintf( fpOut, "  %s (%s) = ",
                    poFDefn->GetNameRef(),
                    OGRFieldDefn::GetFieldTypeName(poFDefn->GetType()) );

            if( IsFieldSet( iField ) )
                fprintf( fpOut, "%s\n", GetFieldAsString( iField ) );
            else
                fprintf( fpOut, "(null)\n" );

        }
    }


    if( GetStyleString() != NULL )
    {
        const char* pszDisplayStyle =
            CSLFetchNameValue(papszOptions, "DISPLAY_STYLE");
        if (pszDisplayStyle == NULL || CSLTestBoolean(pszDisplayStyle))
        {
            fprintf( fpOut, "  Style = %s\n", GetStyleString() );
        }
    }

    if( poGeometry != NULL )
    {
        const char* pszDisplayGeometry =
                CSLFetchNameValue(papszOptions, "DISPLAY_GEOMETRY");
        if ( ! (pszDisplayGeometry != NULL && EQUAL(pszDisplayGeometry, "NO") ) )
            poGeometry->dumpReadable( fpOut, "  ", papszOptions );
    }

    fprintf( fpOut, "\n" );
}
