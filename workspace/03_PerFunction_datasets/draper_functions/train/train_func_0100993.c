mousePressEvent (QGraphicsSceneMouseEvent* event)
{
	if (event->buttons()==Qt::LeftButton) {
		m_widget->mouseBorderClick(position());
	}
}
