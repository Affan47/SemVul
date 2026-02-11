RefreshFriend(uint64 toupdate_id, const wxString& new_name)
{
	wxASSERT( toupdate_id );

	int tab = GetTabByClientID(toupdate_id);

	if (tab != -1) {

		SetPageText(tab,new_name);
	} else {


	}
}
