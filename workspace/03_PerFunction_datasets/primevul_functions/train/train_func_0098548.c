void OpenConnectionTask::startTlsOrLoginNow()
{
    if (model->m_startTls || model->accessParser(parser).capabilities.contains(QLatin1String("LOGINDISABLED"))) {

        Q_ASSERT(model->accessParser(parser).capabilitiesFresh);
        if (!model->accessParser(parser).capabilities.contains(QLatin1String("STARTTLS"))) {
            logout(tr("Server does not support STARTTLS"));
        } else {
            startTlsCmd = parser->startTls();
            model->changeConnectionState(parser, CONN_STATE_STARTTLS_ISSUED);
        }
    } else {

        Q_ASSERT(!model->accessParser(parser).capabilities.contains(QLatin1String("LOGINDISABLED")));
        model->changeConnectionState(parser, CONN_STATE_LOGIN);
        askForAuth();
    }
}
