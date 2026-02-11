ScanGlyfIds(void)
{
	Assert(m_pCmap_3_10 || m_pCmap_3_1);
	if (m_nMaxGlyfId != -1)
		return true;


	unsigned int nUni;
	bool fInUsedRange = false;
	m_cnUnicode = 0;
	for (nUni = 0; nUni <= 0x0010FFFD; nUni++)
	{
		utf16 gid;
		if (nUni == 0x0000FFFE || nUni == 0x0000FFFF)
			gid = 0;
		else
			gid = GlyphFromCmap(nUni, NULL);

        if (gid != 0 && !fInUsedRange)
		{

			m_vnMinUnicode.push_back(nUni);
			fInUsedRange = true;
		}
		else if (gid == 0 && fInUsedRange)
		{

			m_vnLimUnicode.push_back(nUni);
			fInUsedRange = false;
		}
		if (gid != 0)
			m_cnUnicode++;
	}
	if (fInUsedRange)
		m_vnLimUnicode.push_back(nUni);
	Assert(m_vnLimUnicode.size() == m_vnMinUnicode.size());


	unsigned int *prgnUsed = new unsigned int[0x10000];
	if (!prgnUsed)
	{
		g_errorList.AddError(129, NULL,
			"Memory failure: could not allocate prgUsed array when scanning glyph ids");
		return false;
	}

	for (int ig = 0; ig < 0xFFFF; ig++)
		prgnUsed[ig] = 0;
	m_nMaxGlyfId = 0;


	GrcFont::iterator fit;
	GrcFont::iterator fitEnd = this->End();
	for (fit = this->Begin(); fit != fitEnd; ++fit)
	{
		nUni = *fit;
		Assert(nUni != 0x0000FFFE);
		Assert(nUni != 0x0000FFFF);
		Assert(nUni != 0x0010FFFE);
		Assert(nUni != 0x0010FFFF);

		utf16 gid = GlyphFromCmap(nUni, NULL);
		if (gid == 0)
		{
			Assert(false);
			continue;
		}
		m_nMaxGlyfId = max(m_nMaxGlyfId, static_cast<int>(gid));
		if (!prgnUsed[gid])
		{
			prgnUsed[gid] = nUni;
		}
		else
		{

			int nPrevUni = prgnUsed[gid];
			if (nPrevUni != 0x0000FFFF)
			{

				m_vnCollisions.push_back(nPrevUni);


				prgnUsed[gid] = 0x0000FFFF;
			}
			m_vnCollisions.push_back(nUni);
		}
	}
	delete [] prgnUsed;
	return true;
}
