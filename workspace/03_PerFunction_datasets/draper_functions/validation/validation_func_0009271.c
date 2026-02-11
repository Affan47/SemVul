drawTreeMap()
{

  if (!isVisible()) return;

  if (_pixmap.size() != size())
    _needsRefresh = _base;

  if (_needsRefresh) {

    if (DEBUG_DRAWING)
      qDebug() << "Redrawing " << _needsRefresh->path(0).join("/");

    if (_needsRefresh == _base) {

      _pixmap = QPixmap(size());
      _pixmap.fill(palette().color(backgroundRole()));
    }
    QPainter p(&_pixmap);
    if (_needsRefresh == _base) {
      p.setPen(Qt::black);
      p.drawRect(QRect(2, 2, QWidget::width()-5, QWidget::height()-5));
      _base->setItemRect(QRect(3, 3, QWidget::width()-6, QWidget::height()-6));
    }
    else {

      if (!_needsRefresh->itemRect().isValid()) return;
    }


    _font = font();
    _fontHeight = fontMetrics().height();

    drawItems(&p, _needsRefresh);
    _needsRefresh = 0;
  }

  QPainter p(this);
  p.drawPixmap(0, 0, _pixmap, 0, 0,
               QWidget::width(), QWidget::height());

  if (hasFocus()) {
    QStylePainter p(this);
    QStyleOptionFocusRect opt;
    opt.rect = rect();
    opt.palette = palette();
    opt.state = QStyle::State_None;
    p.drawPrimitive( QStyle::PE_FrameFocusRect, opt );
  }
}
