Error()
{
	if (m_pBuffer==NULL) return -1;
	return (m_Position > (long)m_Size);
}
