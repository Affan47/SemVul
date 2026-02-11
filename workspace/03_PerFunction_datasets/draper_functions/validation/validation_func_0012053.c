TranslateGenericName( NTFFileReader *poReader,
                                         OGRNTFLayer *poLayer,
                                         NTFRecord **papoGroup )

{
    int         iRec;

    if( CSLCount((char **) papoGroup) < 2
        || papoGroup[0]->GetType() != NRT_NAMEREC )
        return NULL;

    OGRFeature  *poFeature = new OGRFeature( poLayer->GetLayerDefn() );


    poFeature->SetField( "NAME_ID", atoi(papoGroup[0]->GetField( 3, 8 )) );


    poFeature->SetField( "TEXT_CODE", papoGroup[0]->GetField( 8, 12 ) );


    int nNumChar = atoi(papoGroup[0]->GetField(13,14));

    poFeature->SetField( "TEXT", papoGroup[0]->GetField( 15, 15+nNumChar-1));


    for( iRec = 0; papoGroup[iRec] != NULL; iRec++ )
    {
        if( papoGroup[iRec]->GetType() == NRT_GEOMETRY
            || papoGroup[iRec]->GetType() == NRT_GEOMETRY3D )
        {
            poFeature->SetGeometryDirectly(
                poReader->ProcessGeometry(papoGroup[iRec]));
            poFeature->SetField( "GEOM_ID", papoGroup[iRec]->GetField(3,8) );
            break;
        }
    }


    AddGenericAttributes( poReader, papoGroup, poFeature );


    for( iRec = 0; papoGroup[iRec] != NULL; iRec++ )
    {
        NTFRecord       *poRecord = papoGroup[iRec];

        if( poRecord->GetType() == NRT_NAMEPOSTN )
        {
            poFeature->SetField( "FONT", atoi(poRecord->GetField(3,6)) );
            poFeature->SetField( "TEXT_HT",
                                 atoi(poRecord->GetField(7,9)) * 0.1 );
            poFeature->SetField( "TEXT_HT_GROUND",
                                 atoi(poRecord->GetField(7,9))
                                 * 0.1 * poReader->GetPaperToGround() );
            poFeature->SetField( "DIG_POSTN",
                                 atoi(poRecord->GetField(10,10)) );
            poFeature->SetField( "ORIENT",
                                 atoi(poRecord->GetField(11,14)) * 0.1 );
            break;
        }
    }

    return poFeature;
}
