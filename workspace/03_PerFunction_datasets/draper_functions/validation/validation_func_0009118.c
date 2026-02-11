initAccels()
{
    KActionCollection * localCollection = new KActionCollection( this );

    KAction* next = localCollection->addAction( QLatin1String( "next" ) );
    next->setShortcuts( KStandardShortcut::next() );
    connect( next, SIGNAL(triggered(bool)), SLOT(nextMonth()) );

    KAction* prior = localCollection->addAction( QLatin1String( "prior" ) );
    prior->setShortcuts( KStandardShortcut::prior() );
    connect( prior, SIGNAL(triggered(bool)), SLOT(previousMonth()) );

    KAction* beginMonth = localCollection->addAction( QLatin1String( "beginMonth" ) );
    beginMonth->setShortcuts( KStandardShortcut::begin() );
    connect( beginMonth, SIGNAL(triggered(bool)), SLOT(beginningOfMonth()) );

    KAction* endMonth = localCollection->addAction( QLatin1String( "endMonth" ) );
    endMonth->setShortcuts( KStandardShortcut::end() );
    connect( endMonth, SIGNAL(triggered(bool)), SLOT(endOfMonth()) );

    KAction* beginWeek = localCollection->addAction( QLatin1String( "beginWeek" ) );
    beginWeek->setShortcuts( KStandardShortcut::beginningOfLine() );
    connect( beginWeek, SIGNAL(triggered(bool)), SLOT(beginningOfWeek()) );

    KAction* endWeek = localCollection->addAction( "endWeek" );
    endWeek->setShortcuts( KStandardShortcut::endOfLine() );
    connect( endWeek, SIGNAL(triggered(bool)), SLOT(endOfWeek()) );

    localCollection->readSettings();
    localCollection->addAssociatedWidget( this );
    foreach (QAction* action, localCollection->actions()) {
        action->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    }
}
