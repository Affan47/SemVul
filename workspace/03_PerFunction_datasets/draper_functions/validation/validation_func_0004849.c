createItemWidgets() const
{
    QList<QWidget*> list;

    QLabel * infoLabel = new QLabel();
    infoLabel->setOpenExternalLinks(true);

    ItemsViewDelegate* delegate = const_cast<ItemsViewDelegate*>(this);
    infoLabel->installEventFilter(delegate);
    list << infoLabel;

    QToolButton * installButton = new QToolButton();
    installButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    installButton->setPopupMode(QToolButton::InstantPopup);
    list << installButton;
    setBlockedEventTypes(installButton, QList<QEvent::Type>() << QEvent::MouseButtonPress
                         << QEvent::MouseButtonRelease << QEvent::MouseButtonDblClick);
    connect(installButton, SIGNAL(clicked()), this, SLOT(slotInstallClicked()));
    connect(installButton, SIGNAL(triggered(QAction*)), this, SLOT(slotInstallActionTriggered(QAction*)));

    QToolButton* detailsButton = new QToolButton();
    detailsButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    list << detailsButton;
    setBlockedEventTypes(detailsButton, QList<QEvent::Type>() << QEvent::MouseButtonPress
                         << QEvent::MouseButtonRelease << QEvent::MouseButtonDblClick);
    connect(detailsButton, SIGNAL(clicked()), this, SLOT(slotDetailsClicked()));

    KRatingWidget* rating = new KRatingWidget();
    rating->setMaxRating(10);
    rating->setHalfStepsEnabled(true);
    list << rating;


    return list;
}
