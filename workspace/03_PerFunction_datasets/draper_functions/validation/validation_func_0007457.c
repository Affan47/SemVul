resizeEvent(QResizeEvent *event)
{
    if (event->size().width() != m_widget->width())
        m_widget->resize(event->size().width(), m_widget->height());
    QWidget::resizeEvent(event);
}
