OGRGeocodeGetFromCache(OGRGeocodingSessionH hSession,
                                    const char* pszURL)
{
    CPLMutexHolderD(&hMutex);

    int nIdxBlob = -1;
    OGRLayer* poLayer = OGRGeocodeGetCacheLayer(hSession, FALSE, &nIdxBlob);
    if( poLayer == NULL )
        return NULL;

    char* pszSQLEscapedURL = CPLEscapeString(pszURL, -1, CPLES_SQL);
    poLayer->SetAttributeFilter(CPLSPrintf("%s='%s'", FIELD_URL, pszSQLEscapedURL));
    CPLFree(pszSQLEscapedURL);

    char* pszRet = NULL;
    OGRFeature* poFeature = poLayer->GetNextFeature();
    if( poFeature != NULL )
    {
        if( poFeature->IsFieldSet(nIdxBlob) )
            pszRet = CPLStrdup(poFeature->GetFieldAsString(nIdxBlob));
        OGRFeature::DestroyFeature(poFeature);
    }

    return pszRet;
}
