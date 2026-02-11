AddGlyph(utf16 w)
{
	if (m_wGlyphs.size() == 0)
	{
		m_wGlyphs.push_back(w);
		return;
	}


	if (w > m_wGlyphs.back())
	{
		m_wGlyphs.push_back(w);
		return;
	}

	int iLow = 0;
	int iHigh = m_wGlyphs.size();

	while (iHigh - iLow > 1)
	{
		int iMid = (iHigh + iLow) >> 1;
		if (w == m_wGlyphs[iMid])
			return;

		if (w < m_wGlyphs[iMid])
			iHigh = iMid;
		else
			iLow = iMid;
	}

	if (w < m_wGlyphs[iLow])
		m_wGlyphs.insert(m_wGlyphs.begin() + iLow, w);
	else if (w > m_wGlyphs[iLow])
	{
		Assert(static_cast<size_t>(iHigh) == m_wGlyphs.size() || w < m_wGlyphs[iHigh]);
		m_wGlyphs.insert(m_wGlyphs.begin() + iLow + 1, w);
	}
}
