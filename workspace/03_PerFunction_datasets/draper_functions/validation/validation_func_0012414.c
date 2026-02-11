positionText(QGraphicsItem* item, const QPoint& point)
{
	item->setZValue(m_currentZ++);

	double cx = 0.;
	double cy = (item->boundingRect().bottom() + item->boundingRect().top())/2.;
	if (m_textAlignment == Qt::AlignLeft)
		cx = item->boundingRect().left();
	else if (m_textAlignment == Qt::AlignRight)
		cx = item->boundingRect().right();
	else if (m_textAlignment == Qt::AlignCenter)
		cx = (item->boundingRect().right() + item->boundingRect().left())/2.;

	item->translate(cx, cy);
	item->rotate(-m_textAngle);
	item->translate(-cx, -cy);
	item->setPos(point.x() - cx, point.y() - cy);
}
