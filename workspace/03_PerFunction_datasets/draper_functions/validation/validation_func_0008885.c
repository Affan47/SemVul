makeRecentItem(const QString & objectName, const QString & iconText, const QString & textText, QLabel * & icon, QLabel * & text) {
    QFrame * rFrame = new QFrame;
    QHBoxLayout * rFrameLayout = new QHBoxLayout;

    zeroMargin(rFrameLayout);

    icon = new QLabel(iconText);
    icon->setObjectName("recentIcon");
    connect(icon, SIGNAL(linkActivated(const QString &)), this, SLOT(clickRecent(const QString &)));
    rFrameLayout->addWidget(icon);

	text = new QLabel(textText);
    text->setObjectName(objectName);
    text->setObjectName("recentText");
    rFrameLayout->addWidget(text);
    connect(text, SIGNAL(linkActivated(const QString &)), this, SLOT(clickRecent(const QString &)));

    rFrame->setLayout(rFrameLayout);
    return rFrame;
}
