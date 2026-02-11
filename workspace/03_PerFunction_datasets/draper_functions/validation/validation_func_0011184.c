run()
{
    log_info("new thread running");
    while (!_server.isTerminating() && _server._queue.numWaiting() < _server.minThreads())
    {
        Socket* socket = _server._queue.get();

        if (_server.isTerminating())
        {
            log_debug("server is terminating - quit thread");
            _server._queue.put(socket);
            break;
        }

        if (_server._queue.numWaiting() == 0)
            _server.noWaitingThreads();

        try
        {
            if (!socket->hasAccepted())
            {

                socket->accept();
                log_debug("connection accepted from " << socket->getPeerAddr());

                if (_server.isTerminating())
                {
                    log_debug("server is terminating - quit thread");
                    _server._queue.put(socket);
                    break;
                }


                _server._queue.put(new Socket(*socket));
            }
            else if (socket->isConnected())
            {
                log_debug("process available input");
                socket->onInput(socket->buffer());
            }
            else
            {
                log_debug("socket is not connected any more; delete " << static_cast<void*>(socket));
                delete socket;
                continue;
            }

            Connection inputConnection = connect(socket->buffer().inputReady,
                socket->inputSlot);

            while (socket->wait(10) && socket->isConnected())
                ;

            if (socket->isConnected())
            {
                log_debug("timeout processing socket");
                inputConnection.close();
                _server.addIdleSocket(socket);
            }
            else if (_server.isTerminating())
            {
                _server._queue.put(socket);
            }
            else
            {
                log_debug("socket is not connected any more; delete " << static_cast<void*>(socket));
                delete socket;
            }
        }
        catch (const std::exception& e)
        {
            log_debug("error occured in device: " << e.what() << "; delete " << static_cast<void*>(socket));
            delete socket;
        }
    }

    log_info("thread terminated");
    _server.threadTerminated(this);
}


}
}
