OpenConnectionTask::OpenConnectionTask(Model *model) :
    ImapTask(model)
{

    Q_ASSERT(model->networkPolicy() != NETWORK_OFFLINE);
    parser = new Parser(model, model->m_socketFactory->create(), Common::ConnectionId::next());
    ParserState parserState(parser);
    connect(parser, SIGNAL(responseReceived(Imap::Parser *)), model, SLOT(responseReceived(Imap::Parser*)), Qt::QueuedConnection);
    connect(parser, SIGNAL(connectionStateChanged(Imap::Parser *,Imap::ConnectionState)), model, SLOT(handleSocketStateChanged(Imap::Parser *,Imap::ConnectionState)));
    connect(parser, SIGNAL(lineReceived(Imap::Parser *,QByteArray)), model, SLOT(slotParserLineReceived(Imap::Parser *,QByteArray)));
    connect(parser, SIGNAL(lineSent(Imap::Parser *,QByteArray)), model, SLOT(slotParserLineSent(Imap::Parser *,QByteArray)));
    model->m_parsers[ parser ] = parserState;
    model->m_taskModel->slotParserCreated(parser);
    markAsActiveTask();
}
