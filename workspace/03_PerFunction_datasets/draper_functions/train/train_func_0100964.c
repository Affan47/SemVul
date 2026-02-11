PasswordPrompt(const Barry::BadPassword &bp,
					std::string &password_result)
{

	wxCommandEvent event(MET_PROMPT_PASSWORD, wxID_ANY);
	event.SetEventObject(m_dlg);
	event.SetInt(bp.remaining_tries());
	m_dlg->AddPendingEvent(event);
	m_dlg->WaitForEvent();

	password_result = m_dlg->GetPassword().utf8_str();


	return password_result.size() > 0;
}
