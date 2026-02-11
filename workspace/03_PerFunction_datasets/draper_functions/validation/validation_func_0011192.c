resizeEvent( QResizeEvent* ev )
{
	int newW = ev->size().width();
	int newH = ev->size().height();
	int oldW = ev->oldSize().width();
	int oldH = ev->oldSize().height();

	if(oldW<=0 || oldH<=0)
		return;
	else if( (oldW==newW) && (oldH==newH) )
		return;

	int setSize = qMin(newW, newH);
	QGraphicsView::resize(setSize, setSize);
}
