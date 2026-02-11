paintJobTransfers(QPainter *painter, const qreal &jobAnimationAngle, const QPoint &iconPos, const QStyleOptionViewItemV4& opt)
{
    painter->save();
    QSize iconSize = opt.icon.actualSize(opt.decorationSize);
    QPixmap downArrow = downArrowIcon.pixmap(iconSize * 0.30);

    QPoint bottomRightCorner = QPoint(iconPos.x() + iconSize.width() * 0.75, iconPos.y() + iconSize.height() * 0.60);

    QPainter pixmapPainter(&downArrow);

    pixmapPainter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    pixmapPainter.fillRect(downArrow.rect(), QColor(255, 255, 255, 110));


    painter->translate(bottomRightCorner);

    painter->drawPixmap(-downArrow.size().width() * .50, -downArrow.size().height() * .50, downArrow);


    painter->rotate(jobAnimationAngle);
    painter->setPen(QColor(20, 20, 20, 80));
    painter->setBrush(QColor(250, 250, 250, 90));

    int radius = iconSize.width() * 0.04;
    int spacing = radius * 4.5;


    painter->drawEllipse(QPoint(-spacing, 0), radius, radius);

    painter->drawEllipse(QPoint(spacing, 0), radius, radius);

    painter->drawEllipse(QPoint(0, -spacing), radius, radius);

    painter->drawEllipse(QPoint(0, spacing), radius, radius);
    painter->restore();
}
