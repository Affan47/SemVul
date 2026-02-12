ConnStateData::afterClientRead()
{
#if USE_OPENSSL
    if (parsingTlsHandshake) {
        parseTlsHandshake();
        return;
    }
#endif


    if (pipeline.empty())
        fd_note(clientConnection->fd, "Reading next request");

    if (!clientParseRequests()) {
        if (!isOpen())
            return;


        if (pipeline.empty() && commIsHalfClosed(clientConnection->fd)) {
            debugs(33, 5, clientConnection << ": half-closed connection, no completed request parsed, connection closing.");
            clientConnection->close();
            return;
        }
    }

    if (!isOpen())
        return;

    clientAfterReadingRequests();
}
