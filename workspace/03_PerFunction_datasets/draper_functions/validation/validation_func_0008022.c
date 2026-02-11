GetClosestTo(uint32_t maxType, const CUInt128 &target, uint32_t maxRequired, ContactMap *result, bool emptyFirst, bool inUse) const
{

	if (emptyFirst) {
		result->clear();
	}


#if 0
	if (m_entries.size() == 0) {
#else
	if (m_entries.empty()) {
#endif

		return;
	}


	for (ContactList::const_iterator it = m_entries.begin(); it != m_entries.end(); ++it) {
		if ((*it)->GetType() <= maxType && (*it)->IsIPVerified()) {
			CUInt128 targetDistance((*it)->GetClientID() ^ target);
			(*result)[targetDistance] = *it;

			if (inUse) {
				(*it)->IncUse();
			}
		}
	}


	while (result->size() > maxRequired) {

 		if (inUse) {
  			(--result->end())->second->DecUse();
		}

 		result->erase(--result->end());
	}
}
