CheckSetupTable()

{
    if( szTableName[0] == '\0' )
        return FALSE;


    AVCE00ReadPtr psInfo = ((OGRAVCBinDataSource *) poDS)->GetInfo();
    int           iSection;
    AVCE00Section *psSection = NULL;
    char	  szPaddedName[65];

    sprintf( szPaddedName, "%s%32s", szTableName, " " );
    szPaddedName[32] = '\0';

    for( iSection = 0; iSection < psInfo->numSections; iSection++ )
    {
        if( EQUAL(szPaddedName,psInfo->pasSections[iSection].pszName)
            && psInfo->pasSections[iSection].eType == AVCFileTABLE )
            psSection = psInfo->pasSections + iSection;
    }

    if( psSection == NULL )
    {
        szTableName[0] = '\0';
        return FALSE;
    }


    hTable = AVCBinReadOpen( psInfo->pszInfoPath,  szTableName,
                             psInfo->eCoverType, AVCFileTABLE,
                             psInfo->psDBCSInfo);

    if( hTable == NULL )
    {
        szTableName[0] = '\0';
        return FALSE;
    }


    nTableBaseField = poFeatureDefn->GetFieldCount();

    AppendTableDefinition( hTable->hdr.psTableDef );


    AVCBinReadClose( hTable );

    hTable = NULL;

    return TRUE;
}
