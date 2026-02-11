DebugCmapForMember(GrcFont * pfont,
	utf16 * rgchwUniToGlyphID, unsigned int * rgnGlyphIDToUni)
{
	Assert(m_vwGlyphIDs.size() > 0);


	switch (m_glft)
	{
	case kglftGlyphID:
		break;

	case kglftUnicode:


		break;

	case kglftPostscript:
		break;

	case kglftCodepoint:


		break;

	case kglftPseudo:
		Assert(m_nFirst == 0);
		Assert(m_nLast == 0);
		Assert(m_pglfOutput);

		m_pglfOutput->DebugCmapForMember(pfont, rgchwUniToGlyphID, rgnGlyphIDToUni);

		if (m_nUnicodeInput != 0)
		{


		}
		break;

	default:
		Assert(false);
	}
}
