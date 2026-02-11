eventFilter(QObject *obj, QEvent *ev)
{
    if ( d->topLevel )
    {
	if ( parentWidget() && obj == parentWidget()->topLevelWidget()  )
        {
	    if( ev->type() == QEvent::Resize )
		return false;
#ifdef QT3_SUPPORT
	    if ( ev->type() == QEvent::Accel || ev->type() == QEvent::AccelAvailable )
            {
		if ( QApplication::sendEvent( topLevelWidget(), ev ) )
		    return true;
	    }
#endif


        }
        if( parentWidget() && obj == parentWidget() && ev->type() == QEvent::ParentChange )
            {
            KWindowSystem::setMainWindow( this, parentWidget()->topLevelWidget()->winId());
            setVisible( parentWidget()->isTopLevel() || parentWidget()->isVisible());
            }
        if( parentWidget() && !parentWidget()->isTopLevel() && obj == parentWidget())
        {
            if( ev->type() == QEvent::Show )
                {
                KWindowSystem::setMainWindow( this, parentWidget()->topLevelWidget()->winId());
                show();
                }
            if( ev->type() == QEvent::Hide )
                hide();
	}
    }
    else
    {
        if( parentWidget() && obj == parentWidget()->topLevelWidget())
        {
            if( ev->type() == QEvent::WindowStateChange
                && !parentWidget()->topLevelWidget()->isFullScreen() )
                setTopLevelMenuInternal( d->wasTopLevel );
        }
    }
    return QMenuBar::eventFilter( obj, ev );
}
