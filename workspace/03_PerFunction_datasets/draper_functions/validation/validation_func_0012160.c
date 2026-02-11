mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    QGraphicsItem::mousePressEvent(event);
    if (event->button() == Qt::RightButton) {
        scene()->clearSelection();
        setSelected(true);
        emit requestConfig(event->scenePos().toPoint());
    }
}
