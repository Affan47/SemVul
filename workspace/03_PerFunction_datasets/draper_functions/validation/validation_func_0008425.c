SetProperty(int iIndex, const char *pszValue)
{
    if (iIndex < 0 || iIndex >= m_poDataBlock->GetPropertyCount() ||
	size_t(iIndex) >= m_propertyList.size())
        return FALSE;

    if (strlen(pszValue) < 1)
        m_propertyList[iIndex] = VFKProperty();
    else {
        OGRFieldType fType;

        const char *pszEncoding;
        char       *pszValueEnc;

        fType = m_poDataBlock->GetProperty(iIndex)->GetType();
        switch (fType) {
        case OFTInteger:
            m_propertyList[iIndex] = VFKProperty(atoi(pszValue));
            break;
        case OFTReal:
            m_propertyList[iIndex] = VFKProperty(CPLAtof(pszValue));
            break;
        default:
            pszEncoding = m_poDataBlock->GetProperty(iIndex)->GetEncoding();
            if (pszEncoding) {
                pszValueEnc = CPLRecode(pszValue, pszEncoding,
                                        CPL_ENC_UTF8);
                m_propertyList[iIndex] = VFKProperty(pszValueEnc);
                CPLFree(pszValueEnc);
            }
            else {
                m_propertyList[iIndex] = VFKProperty(pszValue);
            }
            break;
        }
    }
    return TRUE;
}
