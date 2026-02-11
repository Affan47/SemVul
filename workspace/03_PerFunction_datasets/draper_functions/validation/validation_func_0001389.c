StopSearch(uint32_t searchID, bool delayDelete)
{

	for (SearchMap::iterator it = m_searches.begin(); it != m_searches.end(); ++it) {
		if (it->second->GetSearchID() == searchID) {

			if (delayDelete) {
				it->second->PrepareToStop();
			} else {


				delete it->second;
				m_searches.erase(it++);
			}
			return;
		}
	}
}
