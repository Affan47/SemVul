GetCachedFileProp(const char* pszURL)
{
    CPLMutexHolder oHolder( &hMutex );

    CachedFileProp* cachedFileProp = cacheFileSize[pszURL];
    if (cachedFileProp == NULL)
    {
        cachedFileProp = (CachedFileProp*) CPLMalloc(sizeof(CachedFileProp));
        cachedFileProp->eExists = EXIST_UNKNOWN;
        cachedFileProp->bHastComputedFileSize = FALSE;
        cachedFileProp->fileSize = 0;
        cachedFileProp->bIsDirectory = FALSE;
        cacheFileSize[pszURL] = cachedFileProp;
    }

    return cachedFileProp;
}
