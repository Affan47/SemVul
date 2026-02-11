CheckingType() throw()
{
	time_t now = time(NULL);

	if(now - m_lastTypeSet < 10 || m_type == 4) {
		return;
	}

	m_lastTypeSet = now;

	m_expires = now + MIN2S(2);
	m_type++;
}
