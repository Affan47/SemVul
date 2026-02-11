Open( const char *pszFilename,
                                                   const char *pszAccess )
{
    if (strchr(pszAccess, 'w') != NULL ||
        strchr(pszAccess, '+') != NULL)
    {
        CPLError(CE_Failure, CPLE_AppDefined,
                 "Only read-only mode is supported for /vsicurl_streaming");
        return NULL;
    }

    VSICurlStreamingHandle* poHandle = new VSICurlStreamingHandle(
        this, pszFilename + strlen("/vsicurl_streaming/"));

    if (!poHandle->Exists())
    {
        delete poHandle;
        poHandle = NULL;
    }

    if( CSLTestBoolean( CPLGetConfigOption( "VSI_CACHE", "FALSE" ) ) )
        return VSICreateCachedFile( poHandle );
    else
        return poHandle;
}
