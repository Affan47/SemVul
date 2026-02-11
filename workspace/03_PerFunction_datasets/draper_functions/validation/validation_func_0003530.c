paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QStylePainter painter(this);
    painter.setPen(palette().color(QPalette::Text));

    QStyleOptionComboBox opt;
    initStyleOption(&opt);
    painter.drawComplexControl(QStyle::CC_ComboBox, opt);

    QRect frame = style()->subControlRect(QStyle::CC_ComboBox, &opt, QStyle::SC_ComboBoxEditField, this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::transparent);
    painter.setBrush(QBrush(d->internalcolor));
    painter.drawRoundedRect(frame.adjusted(1, 1, -1, -1), 2, 2);
}
