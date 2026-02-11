wheelEvent( QWheelEvent *wev )
{
    QDial::wheelEvent( wev );
    wev->accept();

    const QPoint tooltipPosition = mapToGlobal( rect().translated( 7, -22 ).bottomLeft() );
    QToolTip::showText( tooltipPosition, toolTip() );


    qApp->removeEventFilter( this );

    qApp->installEventFilter( this );
}
