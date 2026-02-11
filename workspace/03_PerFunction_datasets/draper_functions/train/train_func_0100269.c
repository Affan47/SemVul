Open( string openString )
{
	boolean opened = true;
#pragma omp critical
{
	m_ifstream.open(openString.c_str(), ios::in | ios::binary );
	if( m_ifstream.is_open() )
	{
		m_openString = openString;
		if( ParseStream(m_ifstream) )
		{
			;
		}
		else{
			m_ifstream.clear();
			m_ifstream.close();
		}
	}else{
		m_ifstream.clear();
		opened = false;
	}
}
	if(!opened)
		Throw_gnEx(FileNotOpened());
}
