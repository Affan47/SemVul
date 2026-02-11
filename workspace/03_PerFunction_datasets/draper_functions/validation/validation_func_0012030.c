Unget(const byte *inString, size_t length)
{
	size_t len = STDMIN(length, m_head->m_head);
	length -= len;
	m_head->m_head -= len;
	memcpy(m_head->buf + m_head->m_head, inString + length, len);

	if (length > 0)
	{
		ByteQueueNode *newHead = new ByteQueueNode(length);
		newHead->next = m_head;
		m_head = newHead;
		m_head->Put(inString, length);
	}
}
