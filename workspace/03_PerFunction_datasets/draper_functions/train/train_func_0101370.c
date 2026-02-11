escapeXML ()
{
	size_t incr = 0;

	char * ptr = m_psz;
	while (ptr < m_pEnd)
		{
			if ((*ptr == '<') || (*ptr == '>')) incr += 3;
			else if (*ptr == '&') incr += 4;
			else if (*ptr == '"') incr += 5;
			ptr++;
		}
	bool bInsert = grow (incr);

	ptr = m_psz;
	while (ptr < m_pEnd)
		{
			if (*ptr == '<')
				{
					if (bInsert)
						{
							*ptr++ = '&';
							insert (ptr, "lt;", 3);
						}
					else *ptr++ = '?';
				}
			else if (*ptr == '>')
				{
					if (bInsert)
						{
							*ptr++ = '&';
							insert (ptr, "gt;", 3);
						}
					else *ptr++ = '?';
				}
			else if (*ptr == '&')
				{
					if (bInsert)
						{
							*ptr++ = '&';
							insert (ptr, "amp;", 4);
						}
					else *ptr++ = '?';
				}
			else if (*ptr == '"')
				{
					if (bInsert)
						{
							*ptr++ = '&';
							insert (ptr, "quot;", 5);
						}
					else *ptr++ = '?';
				}
			else ptr++;
		}
}
