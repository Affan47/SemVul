setCurrentMap(const char * szName)
{
	UT_uint32 kLimit = m_vecNames.getItemCount();
	UT_uint32 k;

	for (k=0; k<kLimit; k++)
		if (g_ascii_strcasecmp(szName,reinterpret_cast<const char *>(m_vecNames.getNthItem(k))) == 0)
		{
			m_indexCurrentEventMap = k;
			return true;
		}

	return false;
}
