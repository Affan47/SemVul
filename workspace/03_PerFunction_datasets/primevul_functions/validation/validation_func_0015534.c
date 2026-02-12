ConnStateData::splice()
{


    if (fd_table[clientConnection->fd].ssl.get()) {

        fd_table[clientConnection->fd].read_method = &default_read_method;
        fd_table[clientConnection->fd].write_method = &default_write_method;
    }


    transferProtocol = Http::ProtocolVersion();
    assert(!pipeline.empty());
    Http::StreamPointer context = pipeline.front();
    Must(context);
    Must(context->http);
    ClientHttpRequest *http = context->http;
    HttpRequest::Pointer request = http->request;
    context->finished();
    if (transparent()) {


        return fakeAConnectRequest("splice", preservedClientData);
    } else {


        return initiateTunneledRequest(request, Http::METHOD_CONNECT, "splice", preservedClientData);
    }
}
