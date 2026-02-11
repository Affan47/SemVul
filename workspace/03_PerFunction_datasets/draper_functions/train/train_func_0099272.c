ComparePriorUserhash(uint32 dwIP, uint16 nPort, void* pNewHash)
{
	std::map<uint32, CDeletedClient*>::iterator it = m_trackedClientsList.find( dwIP );

	if ( it != m_trackedClientsList.end() ) {
		CDeletedClient* pResult = it->second;

		CDeletedClient::PaHList::iterator it2 = pResult->m_ItemsList.begin();
		for ( ; it2 != pResult->m_ItemsList.end(); ++it2 ) {
			if ( it2->nPort == nPort ) {
				if ( it2->pHash != pNewHash) {
					return false;
				} else {
					break;
				}
			}
		}
	}
	return true;
}
