resizeEvent(QResizeEvent* event)
{
    if (scene() != 0)
        fitInView(scene()->sceneRect().adjusted(0, 0, 30, 30), Qt::KeepAspectRatio);

    QGraphicsView::resizeEvent(event);
}
