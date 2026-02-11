httpOmitBody(HttpConn *conn)
{
    if (conn->tx) {
        conn->tx->flags |= HTTP_TX_NO_BODY;
    }
    if (conn->tx->flags & HTTP_TX_HEADERS_CREATED) {
        mprError("Can't set response body if headers have already been created");

    } else {
        httpDiscardTransmitData(conn);
    }
}
