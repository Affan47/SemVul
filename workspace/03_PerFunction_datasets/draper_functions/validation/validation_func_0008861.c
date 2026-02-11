OnButton(wxCommandEvent& event)
{
	if (event.GetId() == m_pAdd->GetId())
	{
		OnMore();
		return;
	}

	for (int i = 0; i < (int)m_filterControls.size(); i++)
	{
		if (m_filterControls[i].pRemove->GetId() == event.GetId())
		{
			OnRemove(i);
			return;
		}
	}
	event.Skip();
}
