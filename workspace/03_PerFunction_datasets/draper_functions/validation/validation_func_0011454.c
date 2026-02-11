AddTrackClient(CUpDownClient* toadd)
{
	std::map<uint32, CDeletedClient*>::iterator it = m_trackedClientsList.find( toadd->GetIP() );

	if ( it != m_trackedClientsList.end() ) {
		CDeletedClient* pResult = it->second;

		pResult->m_dwInserted = ::GetTickCount();

		CDeletedClient::PaHList::iterator it2 = pResult->m_ItemsList.begin();
		for ( ; it2 != pResult->m_ItemsList.end(); ++it2 ) {
			if ( it2->nPort == toadd->GetUserPort() ) {

				it2->pHash = toadd->GetCreditsHash();
				return;
			}
		}


		CDeletedClient::PortAndHash porthash = { toadd->GetUserPort(), toadd->GetCreditsHash()};
		pResult->m_ItemsList.push_back(porthash);
	} else {
		m_trackedClientsList[ toadd->GetIP() ] = new CDeletedClient(toadd);
	}
}
