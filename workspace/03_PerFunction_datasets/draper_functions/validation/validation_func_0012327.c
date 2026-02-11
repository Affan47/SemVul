cacheBackground(const QSize &size, bool expanded)
{
    QPixmap pixmap(size);
    pixmap.fill(Qt::transparent);
    QPainter p(&pixmap);

    int topHeight = m_useCheckBox ? m_summaryCheckBox->height() : m_summaryLabel->height();
    if (m_state == DetailsWidget::Expanded || m_state == DetailsWidget::Collapsed)
        topHeight = qMax(m_detailsButton->height(), topHeight);

    QRect topRect(0, 0, size.width(), topHeight);
    QRect fullRect(0, 0, size.width(), size.height());
#ifdef Q_OS_MAC
    p.fillRect(fullRect, qApp->palette().window().color());
#endif
    p.fillRect(fullRect, QColor(255, 255, 255, 40));

    QColor highlight = q->palette().highlight().color();
    highlight.setAlpha(0);
    if (expanded)
        p.fillRect(topRect, highlight);

    QLinearGradient lg(topRect.topLeft(), topRect.bottomLeft());
    lg.setColorAt(0, QColor(255, 255, 255, 130));
    lg.setColorAt(1, QColor(255, 255, 255, 0));
    p.fillRect(topRect, lg);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.translate(0.5, 0.5);
    p.setPen(QColor(0, 0, 0, 40));
    p.setBrush(Qt::NoBrush);
    p.drawRoundedRect(fullRect.adjusted(0, 0, -1, -1), 2, 2);
    p.setBrush(Qt::NoBrush);
    p.setPen(QColor(255,255,255,140));
    p.drawRoundedRect(fullRect.adjusted(1, 1, -2, -2), 2, 2);
    p.setPen(QPen(q->palette().color(QPalette::Mid)));

    return pixmap;
}
