FindNext(int nIndexNumber, GByte *pKeyValue)
{
    if (ValidateIndexNo(nIndexNumber) != 0)
        return -1;

    return m_papoIndexRootNodes[nIndexNumber-1]->FindNext(pKeyValue);
}
