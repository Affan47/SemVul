shadowText(QString text, const QFont &font, QColor textColor, QColor shadowColor, QPoint offset, int radius)
{

    if (text.isEmpty()) {
        return QPixmap();
    }


    QFontMetrics fm(font);
    QRect textRect = fm.boundingRect(text);
    QPixmap textPixmap(textRect.width(), fm.height());
    textPixmap.fill(Qt::transparent);
    QPainter p(&textPixmap);
    p.setPen(textColor);
    p.setFont(font);


    p.drawText(textPixmap.rect(), Qt::AlignCenter, text);
    p.end();


    QImage img(textRect.size() + QSize(radius * 2, radius * 2), QImage::Format_ARGB32_Premultiplied);
    img.fill(0);
    p.begin(&img);
    p.drawImage(QPoint(radius, radius), textPixmap.toImage());
    p.end();
    shadowBlur(img, radius, shadowColor);


    int addSizeX = qMax(0, qAbs(offset.x()) - radius);
    int addSizeY = qMax(0, qAbs(offset.y()) - radius);

    QPixmap finalPixmap(img.size() + QSize(addSizeX, addSizeY));
    finalPixmap.fill(Qt::transparent);
    p.begin(&finalPixmap);
    p.drawImage(qMax(0, offset.x()), qMax(0, offset.y()), img);
    p.drawPixmap(radius + qMax(0, -offset.x()), radius + qMax(0, -offset.y()), textPixmap);
    p.end();

    return finalPixmap;
}
