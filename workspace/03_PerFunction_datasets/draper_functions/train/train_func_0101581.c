ParseHello( const CString & sContent )
{
	CMessageHello * msg = new CMessageHello();

	msg->m_sNick = m_pRemoteToLocal->encode(sContent);

	return msg;
}
