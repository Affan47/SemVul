addStyle(const std::string & sStyle)
{
	UT_UTF8String * psStyle = new UT_UTF8String(sStyle);
	m_vecStyles.addItem(psStyle);
}
