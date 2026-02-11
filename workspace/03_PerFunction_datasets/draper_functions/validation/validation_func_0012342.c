Validate()
{
	if (GetRCheck(XRCID("ID_DATEFORMAT_CUSTOM")) && XRCCTRL(*this, "ID_CUSTOM_DATEFORMAT", wxTextCtrl)->GetValue() == _T(""))
		return DisplayError(_T("ID_CUSTOM_DATEFORMAT"), _("Please enter a custom date format."));

	if (GetRCheck(XRCID("ID_TIMEFORMAT_CUSTOM")) && XRCCTRL(*this, "ID_CUSTOM_TIMEFORMAT", wxTextCtrl)->GetValue() == _T(""))
		return DisplayError(_T("ID_CUSTOM_TIMEFORMAT"), _("Please enter a custom time format."));

	return true;
}
