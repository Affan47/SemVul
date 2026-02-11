GetListenHostString()
{
	m_Mutex.Lock();

	CString s;

	if ( m_sListenHost.NotEmpty() )
	{
		s = CNetAddr::GetHostI4(m_sListenHost.Replace(' ',""));
	}

	m_Mutex.UnLock();

	return s;
}
