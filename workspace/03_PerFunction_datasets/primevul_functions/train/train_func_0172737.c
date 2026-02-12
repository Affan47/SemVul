void CjfifDecode::SetStatusText(CString strText)
{


	if (m_pStatBar) {
		m_pStatBar->SetPaneText(0,strText);
	}
}
