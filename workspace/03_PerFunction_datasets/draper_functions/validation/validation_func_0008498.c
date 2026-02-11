SetFeaturePropertyDirectly( const char *pszElement,
                                            char *pszValue,
                                            int iPropertyIn )

{
    GMLFeature *poFeature = GetState()->m_poFeature;

    CPLAssert( poFeature  != NULL );


    GMLFeatureClass *poClass = poFeature->GetClass();
    int      iProperty;

    int nPropertyCount = poClass->GetPropertyCount();
    if (iPropertyIn >= 0 && iPropertyIn < nPropertyCount)
    {
        iProperty = iPropertyIn;
    }
    else
    {
        for( iProperty=0; iProperty < nPropertyCount; iProperty++ )
        {
            if( strcmp(poClass->GetProperty( iProperty )->GetSrcElement(),
                    pszElement ) == 0 )
                break;
        }

        if( iProperty == nPropertyCount )
        {
            if( poClass->IsSchemaLocked() )
            {
                CPLDebug("GML","Encountered property missing from class schema.");
                CPLFree(pszValue);
                return;
            }

            CPLString osFieldName;

            if( strchr(pszElement,'|') == NULL )
                osFieldName = pszElement;
            else
            {
                osFieldName = strrchr(pszElement,'|') + 1;
                if( poClass->GetPropertyIndex(osFieldName) != -1 )
                    osFieldName = pszElement;
            }


            while( poClass->GetProperty(osFieldName) != NULL )
            {
                osFieldName += "_";
            }

            GMLPropertyDefn *poPDefn = new GMLPropertyDefn(osFieldName,pszElement);

            if( EQUAL(CPLGetConfigOption( "GML_FIELDTYPES", ""), "ALWAYS_STRING") )
                poPDefn->SetType( GMLPT_String );

            if (poClass->AddProperty( poPDefn ) < 0)
            {
                delete poPDefn;
                CPLFree(pszValue);
                return;
            }
        }
    }


    poFeature->SetPropertyDirectly( iProperty, pszValue );


    if( !poClass->IsSchemaLocked() )
    {
        poClass->GetProperty(iProperty)->AnalysePropertyValue(
                             poFeature->GetProperty(iProperty));
    }
}
