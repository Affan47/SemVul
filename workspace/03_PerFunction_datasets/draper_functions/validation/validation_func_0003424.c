onOutput(StreamBuffer& sb)
{
    log_trace("ClientImpl::onOutput; out_avail=" << sb.out_avail());

    try
    {
        try
        {
            _errorPending = false;

            sb.endWrite();

            if( sb.out_avail() > 0 )
            {
                sb.beginWrite();
            }
            else
            {
                sb.beginRead();
                _client->requestSent(*_client);
                _parser.reset(true);
                _readHeader = true;
            }
        }
        catch (const IOError& e)
        {
            if (_reconnectOnError && _request != 0)
            {
                log_debug("reconnect on error");
                _socket.close();
                _reconnectOnError = false;
                reexecuteBegin(*_request);
                return;
            }

            throw;
        }
    }
    catch (const std::exception& e)
    {
        log_warn("error of type " << typeid(e).name() << " occured: " << e.what());

        _errorPending = true;

        _client->replyFinished(*_client);

        if (_errorPending)
            throw;
    }
}
