gotoBookmark()
{
	if (!m_didBookmark)
		return 0;
	m_current = m_bookmark.current;
	m_data = m_bookmark.data;
	m_eos = m_bookmark.eos;
	m_left = m_bookmark.left;
	m_len = m_bookmark.len;
	return 1;
}
