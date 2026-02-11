ReorderFields( int* panMap )
{
    if (!bUpdatable)
        return OGRERR_FAILURE;

    if (poFeatureDefn->GetFieldCount() == 0)
        return OGRERR_NONE;

    OGRErr eErr = OGRCheckPermutation(panMap, poFeatureDefn->GetFieldCount());
    if (eErr != OGRERR_NONE)
        return eErr;


    for( int i = 0; i < nMaxFeatureCount; i++ )
    {
        if( papoFeatures[i] != NULL )
            papoFeatures[i]->RemapFields( NULL, panMap );
    }

    return poFeatureDefn->ReorderFieldDefns( panMap );
}
