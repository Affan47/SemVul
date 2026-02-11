updateFallbackSize()
{
    if( !d->topLevel )
	return;
#ifdef Q_WS_X11
    if( d->selection->owner() != None )
#endif
    {

        d->selection_timer.stop();
        if( d->fallback_mode )
        {
            d->fallback_mode = false;
            KWindowSystem::setStrut( winId(), 0, 0, 0, 0 );
            setMinimumSize( 0, 0 );
            setMaximumSize( QWIDGETSIZE_MAX, QWIDGETSIZE_MAX );
            updateMenuBarSize();
        }
	return;
    }
    if( d->selection_timer.isActive())
	return;
    d->selection_timer.setInterval(100);
    d->selection_timer.setSingleShot(true);
    d->selection_timer.start();
}
