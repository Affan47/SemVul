OnButtonPortTest(wxCommandEvent& WXUNUSED(evt))
{
	if (theApp && theApp->amuledlg) {
		wxString portTestURL = wxString::Format(wxT(ADU_PORTTEST_BASE_URL),
			CastChild( IDC_PORT, wxSpinCtrl)->GetValue(),
			CastChild( IDC_UDPPORT, wxSpinCtrl)->GetValue());
		theApp->amuledlg->LaunchUrl(portTestURL);
	}
}
