paintFrontView(QPainter *painter, const QRectF &rect)
{

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);
    painter->setRenderHint(QPainter::HighQualityAntialiasing, true);

    QPainterPath backgroundPath;
    backgroundPath.addRoundedRect(rect, 3.5, 3.5);

    QLinearGradient linearGrad(QPointF(0, 0), QPointF(0.0 , rect.height()));


    linearGrad.setColorAt(1, QColor(189, 191, 196));
    linearGrad.setColorAt(0, QColor(255, 255, 255));

    painter->fillPath(backgroundPath, linearGrad);
    QPen pen(QColor(98, 101, 108), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);
    painter->drawPath(backgroundPath);
}
