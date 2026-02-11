setState(State state)
{
	if (state == m_state)
		return;
	if (m_state == Thinking)
		emit stoppedThinking();

	m_state = state;
}
