RemoveFile(const CServer &server, const CServerPath &path, const wxString& filename)
{
	tServerIter sit = GetServerEntry(server);
	if (sit == m_serverList.end())
		return false;

	for (tCacheIter iter = sit->cacheList.begin(); iter != sit->cacheList.end(); ++iter)
	{
		const CCacheEntry &entry = *iter;
		if (path.CmpNoCase(entry.listing.path))
			continue;

		UpdateLru(sit, iter);

		bool matchCase = false;
		for (unsigned int i = 0; i < entry.listing.GetCount(); i++)
		{
			if (entry.listing[i].name == filename)
				matchCase = true;
		}

		if (matchCase)
		{
			unsigned int i;
			for (i = 0; i < entry.listing.GetCount(); i++)
				if (entry.listing[i].name == filename)
					break;
			wxASSERT(i != entry.listing.GetCount());

			CDirectoryListing& listing = iter->listing;
			listing.RemoveEntry(i);
			--m_totalFileCount;
		}
		else
		{
			for (unsigned int i = 0; i < entry.listing.GetCount(); i++)
			{
				if (!filename.CmpNoCase(entry.listing[i].name))
					iter->listing[i].flags |= CDirentry::flag_unsure;
			}
			iter->listing.m_hasUnsureEntries |= CDirectoryListing::unsure_invalid;
		}
		iter->modificationTime = CTimeEx::Now();
	}

	return true;
}
