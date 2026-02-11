setMessageType(KMessageWidget::MessageType type)
{
    d->messageType = type;
    QColor bg0, bg1, bg2, border, fg;
    switch (type) {
    case Positive:
        getColorsFromColorScheme(KColorScheme::PositiveBackground, &bg1, &fg);
        break;
    case Information:


        bg1 = palette().highlight().color();
        fg = palette().highlightedText().color();
        break;
    case Warning:
        getColorsFromColorScheme(KColorScheme::NeutralBackground, &bg1, &fg);
        break;
    case Error:
        getColorsFromColorScheme(KColorScheme::NegativeBackground, &bg1, &fg);
        break;
    }


    bg0 = bg1.lighter(110);
    bg2 = bg1.darker(110);
    border = KColorScheme::shade(bg1, KColorScheme::DarkShade);

    d->content->setStyleSheet(
        QString(".QFrame {"
            "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
            "    stop: 0 %1,"
            "    stop: 0.1 %2,"
            "    stop: 1.0 %3);"
            "border-radius: 5px;"
            "border: 1px solid %4;"
            "margin: %5px;"
            "}"
            ".QLabel { color: %6; }"
            )
        .arg(bg0.name())
        .arg(bg1.name())
        .arg(bg2.name())
        .arg(border.name())

        .arg(style()->pixelMetric(QStyle::PM_DefaultFrameWidth, 0, this) -1)
        .arg(fg.name())
        );
}
