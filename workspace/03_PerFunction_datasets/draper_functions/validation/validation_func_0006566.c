ping()
{
	if (m_pinging
	||  state() == NotStarted
	||  state() == Disconnected
	||  !sendPing())
		return;

	m_pinging = true;
	m_pingState = state();
	m_pingTimer->start();
}
