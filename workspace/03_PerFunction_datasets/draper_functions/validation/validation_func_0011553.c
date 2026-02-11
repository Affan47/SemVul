mouseMoveEvent(QMouseEvent *event)
{
#ifndef QT_NO_DRAGANDDROP
    if (event->buttons() & Qt::LeftButton &&
            (d_ptr->m_dragStart - event->pos()).manhattanLength() > QApplication::startDragDistance()) {
        QMimeData *mime = new QMimeData;
        mime->setColorData(color());
        QDrag *drg = new QDrag(this);
        drg->setMimeData(mime);
        drg->setPixmap(d_ptr->generatePixmap());
        setDown(false);
        event->accept();
        drg->start();
        return;
    }
#endif
    QToolButton::mouseMoveEvent(event);
}
