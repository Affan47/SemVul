sysInstall()
{
	if ( d )
		return;

	if ( v_isWMDock )
		d = (TrayIconPrivate *)(new TrayIconWindowMaker(this, pm));
	else
		d = (TrayIconPrivate *)(new TrayIconFreeDesktop(this, pm));

	sysUpdateToolTip();

	if ( v_isWMDock )
		d->show();
}
