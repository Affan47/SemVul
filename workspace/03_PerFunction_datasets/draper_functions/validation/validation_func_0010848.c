UpdateMenuState()
{
	if( !m_sysmenu.get() )
		return;

	wxMenuItemList &list = m_sysmenu->GetMenuItems();
	wxMenuItemList::iterator b = list.begin();
	for( ; b != list.end(); ++b ) {
		wxMenuItem *item = *b;

		switch( item->GetId() )
		{
		case SysMenu_VerboseLogging:
			item->Check(Barry::IsVerbose());
			break;
		}
	}
}
