ConnStateData::requestTimeout(const CommTimeoutCbParams &io)
{
    if (!Comm::IsConnOpen(io.conn))
        return;

    const err_type error = receivedFirstByte_ ? ERR_REQUEST_PARSE_TIMEOUT : ERR_REQUEST_START_TIMEOUT;
    if (tunnelOnError(HttpRequestMethod(), error))
        return;


    debugs(33, 3, "requestTimeout: FD " << io.fd << ": lifetime is expired.");
    io.conn->close();
}
