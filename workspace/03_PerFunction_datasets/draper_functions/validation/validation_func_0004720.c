SDTSScanModuleReferences( DDFModule * poModule, const char * pszFName )

{


    DDFFieldDefn        *poIDField;
    DDFSubfieldDefn     *poMODN;

    poIDField = poModule->FindFieldDefn( pszFName );

    if( poIDField == NULL )
        return NULL;

    poMODN = poIDField->FindSubfieldDefn( "MODN" );
    if( poMODN == NULL )
        return NULL;


    DDFRecord   *poRecord;
    char        **papszModnList = NULL;

    poModule->Rewind();
    while( (poRecord = poModule->ReadRecord()) != NULL )
    {
        int     iField;

        for( iField = 0; iField < poRecord->GetFieldCount(); iField++ )
        {
            DDFField    *poField = poRecord->GetField( iField );

            if( poField->GetFieldDefn() == poIDField )
            {
                const char      *pszModName;
                int             i;

                for( i = 0; i < poField->GetRepeatCount(); i++ )
                {
                    char        szName[5];

                    pszModName = poField->GetSubfieldData(poMODN,NULL,i);

                    strncpy( szName, pszModName, 4 );
                    szName[4] = '\0';

                    if( CSLFindString( papszModnList, szName ) == -1 )
                        papszModnList = CSLAddString( papszModnList, szName );
                }
            }
        }
    }

    poModule->Rewind();

    return papszModnList;
}
