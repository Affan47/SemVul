paintEvent( QPaintEvent* e)
{


  QPainter     paint( this );


  paint.setFont(font());
  const QPalette& p = qApp->palette();
  paint.setBrush(p.background());

  if( _labelBBox.intersects(e->rect()) ) {
    paintLabels(&paint);
  }

  QString text;
  if( !getDisplayText(text) ) {
      cerr << "[error] - internal inconsitency. Please file bug report."
	   << endl;
      return;
  }


  drawCursor( paint );
  drawSelection( paint );


  int totalWordWidth = wordWidth()+wordSpacing();
  int row_start = max(0,(e->rect().top()-topMargin())/lineSpacing() );
  int col_start = max(0,(e->rect().left()-leftMargin())/totalWordWidth);
  int row_stop  = min(_rows-1,e->rect().bottom() / lineSpacing());
  int col_stop  = min(_cols-1,e->rect().right() / totalWordWidth);


  drawTextRegion( paint, text, row_start, row_stop, col_start, col_stop );
}
