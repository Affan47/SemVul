OnChar(wxKeyEvent& event)
{
	if (event.GetKeyCode() == WXK_ESCAPE)
	{
		wxCommandEvent event(wxEVT_COMMAND_BUTTON_CLICKED, wxID_CANCEL);
		ProcessEvent(event);
	}
	else
		event.Skip();
}
