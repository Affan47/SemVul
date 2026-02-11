AppendUser( CString & nick, bool getinfo )
{
	bool res = false;

	if ( nick.IsEmpty() )
	{
		return res;
	}

	CMessageMyInfo *myinfo=0;

	m_Mutex.Lock();

	MyInfoMap::iterator it = m_MyInfoMap.find(nick);
	if ( it == m_MyInfoMap.end() )
	{
		myinfo = new CMessageMyInfo();
		myinfo->m_sNick     = nick;
		myinfo->m_eAwayMode = euamNORMAL;

		m_MyInfoMap[nick] = myinfo;

		if ( getinfo )
			res = true;
	}

	m_Mutex.UnLock();

	return res;
}
