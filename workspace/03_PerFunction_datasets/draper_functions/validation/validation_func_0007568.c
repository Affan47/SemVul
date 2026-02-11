getClientList() const
{
	WindowManager::Property <Window> *p =
		new WindowManager::Property <Window>();

	if( !p->getProperty( display, root, XA_WINDOW, "_NET_CLIENT_LIST" ) )
		p->getProperty( display, root, XA_CARDINAL, "_WIN_CLIENT_LIST" );

	return WindowManager::WindowList( p );
}
