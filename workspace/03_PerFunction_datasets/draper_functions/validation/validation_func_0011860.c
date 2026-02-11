httpSetUri(HttpConn *conn, cchar *uri, cchar *query)
{
    HttpRx      *rx;
    HttpTx      *tx;
    HttpUri     *prior;

    rx = conn->rx;
    tx = conn->tx;
    prior = rx->parsedUri;

    if ((rx->parsedUri = httpCreateUri(uri, 0)) == 0) {
        return MPR_ERR_BAD_ARGS;
    }
    if (prior) {
        if (rx->parsedUri->scheme == 0) {
            rx->parsedUri->scheme = prior->scheme;
        }
        if (rx->parsedUri->port == 0) {
            rx->parsedUri->port = prior->port;
        }
    }
    if (query == 0 && prior) {
        rx->parsedUri->query = prior->query;
        rx->parsedUri->host = prior->host;
    } else if (*query) {
        rx->parsedUri->query = sclone(query);
    }


    rx->uri = rx->parsedUri->path;
    rx->pathInfo = httpNormalizeUriPath(mprUriDecode(rx->parsedUri->path));
    rx->scriptName = mprEmptyString();
    tx->ext = httpGetExt(conn);
    return 0;
}
