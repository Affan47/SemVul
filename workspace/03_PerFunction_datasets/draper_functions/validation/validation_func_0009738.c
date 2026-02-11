GDALPDFGetValueFromDSOrOption(GDALDataset* poSrcDS,
                                                 char** papszOptions,
                                                 const char* pszKey)
{
    const char* pszValue = CSLFetchNameValue(papszOptions, pszKey);
    if (pszValue == NULL)
        pszValue = poSrcDS->GetMetadataItem(pszKey);
    if (pszValue != NULL && pszValue[0] == '\0')
        return NULL;
    else
        return pszValue;
}
