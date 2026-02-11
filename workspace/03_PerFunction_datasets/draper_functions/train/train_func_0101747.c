OnUnderlineChanged (unsigned underline)
{
	switch (underline) {
	default:
		m_Underline = gccv::TextDecorationNone;
		break;
	case 1:
		m_Underline = gccv::TextDecorationDefault;
		break;
	case 2:
		m_Underline = gccv::TextDecorationDouble;
		break;
	case 3:
		m_Underline = gccv::TextDecorationLow;
		break;
	}
	BuildTagsList ();
	if (m_Active) {
		gccv::TextTagList l;
		l.push_front (new gccv::UnderlineTextTag (m_Underline));
		m_Active->ApplyTagsToSelection (&l);
	}
}
