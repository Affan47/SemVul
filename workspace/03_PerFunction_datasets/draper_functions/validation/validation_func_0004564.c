isstringstart(ichar_t c)
{
	if (c < (SET_SIZE))
		return m_hashheader.stringstarts[static_cast<unsigned char>(c)];
	else
		return 0;
}
