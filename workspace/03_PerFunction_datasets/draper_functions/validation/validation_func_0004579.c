OnViewFiles(wxCommandEvent& WXUNUSED(event))
{
	long index = GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );

	while( index != -1 ) {
		CFriend* cur_friend = (CFriend*)GetItemData(index);
		theApp->friendlist->RequestSharedFileList(cur_friend);
		index = GetNextItem( index, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
	}

}
