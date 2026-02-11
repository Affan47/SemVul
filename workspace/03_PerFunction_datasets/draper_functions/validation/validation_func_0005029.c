charData (const gchar * str, int len)
{
	if (m_bContinue == false) return;

	if ((m_ePM!=pm_parse) || (cb_text==0)) return;

	if ((m_bIsText && (m_bHasTSpan==false)) || m_bIsTSpan)
	{
		if (m_pBB == 0) m_pBB = new UT_ByteBuf;

		if (!(m_pBB->append(reinterpret_cast<const UT_Byte *>(str), static_cast<UT_uint32>(len))))
		{
			UT_DEBUGMSG(("SVG: parse error: insufficient memory?\n"));
			m_bSVG = false;
			m_bContinue = false;
		}
	}
}
