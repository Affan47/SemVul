enterPersistMode()
{
	setQuitOnLastWindowClosed(true);

	if (m_windows.isEmpty())
		quit();


	freopen("/dev/null","w",stdout);
	freopen("/dev/null","w",stderr);
}
