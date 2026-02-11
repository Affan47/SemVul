GDALWriteIMDMultiLine( VSILFILE *fp, const char *pszValue )

{
    char **papszItems = CSLTokenizeStringComplex( pszValue, "(,) ",
                                                  FALSE, FALSE );
    int nItemCount = CSLCount(papszItems);
    int i;

    VSIFPrintfL( fp, "(\n" );

    for( i = 0; i < nItemCount; i++ )
    {
        if( i == nItemCount-1 )
            VSIFPrintfL( fp, "\t%s );\n", papszItems[i] );
        else
            VSIFPrintfL( fp, "\t%s,\n", papszItems[i] );
    }
    CSLDestroy( papszItems );
}
