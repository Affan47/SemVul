OnOK(wxCommandEvent& event)
{
	long download, upload;
	wxTextCtrl* pCtrl = XRCCTRL(*this, "ID_DOWNLOADLIMIT", wxTextCtrl);
	if (!pCtrl->GetValue().ToLong(&download) || (download < 0))
	{
		const wxString unit = CSizeFormat::GetUnitWithBase(CSizeFormat::kilo, 1024);
		wxMessageBox(wxString::Format(_("Please enter a download speed limit greater or equal to 0 %s/s."), unit.c_str()), _("Speed Limits"), wxOK, this);
		return;
	}

	pCtrl = XRCCTRL(*this, "ID_UPLOADLIMIT", wxTextCtrl);
	if (!pCtrl->GetValue().ToLong(&upload) || (upload < 0))
	{
		const wxString unit = CSizeFormat::GetUnitWithBase(CSizeFormat::kilo, 1024);
		wxMessageBox(wxString::Format(_("Please enter an upload speed limit greater or equal to 0 %s/s."), unit.c_str()), _("Speed Limits"), wxOK, this);
		return;
	}

	COptions::Get()->SetOption(OPTION_SPEEDLIMIT_INBOUND, download);
	COptions::Get()->SetOption(OPTION_SPEEDLIMIT_OUTBOUND, upload);

	bool enable = XRCCTRL(*this, "ID_ENABLE_SPEEDLIMITS", wxCheckBox)->GetValue() ? 1 : 0;
	COptions::Get()->SetOption(OPTION_SPEEDLIMIT_ENABLE, enable && (download || upload));

	EndDialog(wxID_OK);
}
