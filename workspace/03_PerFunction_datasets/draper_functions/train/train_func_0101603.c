Clone()
{
    GDALPDFDictionaryRW* poDict = new GDALPDFDictionaryRW();
    std::map<CPLString, GDALPDFObject*>& oMap = GetValues();
    std::map<CPLString, GDALPDFObject*>::iterator oIter = oMap.begin();
    std::map<CPLString, GDALPDFObject*>::iterator oEnd = oMap.end();
    for(;oIter != oEnd;++oIter)
    {
        const char* pszKey = oIter->first.c_str();
        GDALPDFObject* poObj = oIter->second;
        poDict->Add(pszKey, poObj->Clone());
    }
    return poDict;
}
