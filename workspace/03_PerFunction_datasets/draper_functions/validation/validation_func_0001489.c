hoverEnterEvent (QGraphicsSceneHoverEvent*)
{
	if (m_timer==NULL) {
		m_timer = new QTimer(this);
		connect(m_timer, SIGNAL(timeout()), this, SLOT(showInteractions()));
		m_timer->start(TIME_TO_WAIT_BEFORE_SHOWING_INTERACTIONS);
	}
}
