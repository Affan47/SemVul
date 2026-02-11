ReduceLength(lword delta)
{
	if (m_definiteLength)
	{
		if (m_length < delta)
			BERDecodeError();
		m_length -= delta;
	}
	return delta;
}
