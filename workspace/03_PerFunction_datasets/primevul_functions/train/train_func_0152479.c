AbstractWebApplication::AbstractWebApplication(QObject *parent)
    : Http::ResponseBuilder(parent)
    , session_(0)
{
    QTimer *timer = new QTimer(this);
    timer->setInterval(60000);
    connect(timer, SIGNAL(timeout()), SLOT(removeInactiveSessions()));
}
