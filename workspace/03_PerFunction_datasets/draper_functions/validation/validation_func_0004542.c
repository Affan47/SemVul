mouseDoubleClickEvent( QMouseEvent *e )
{
	if ( e->button() == Qt::LeftButton )
		emit doubleClicked( e->globalPos() );
	e->accept();
}
