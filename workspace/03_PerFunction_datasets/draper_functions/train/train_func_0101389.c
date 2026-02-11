getPacket(HttpConn *conn, ssize *size)
{
    HttpPacket  *packet;
    MprBuf      *content;

    if ((packet = conn->input) == NULL) {
        conn->input = packet = httpCreatePacket(HTTP_BUFSIZE);
    } else {
        content = packet->content;
        mprResetBufIfEmpty(content);
        mprAddNullToBuf(content);
        if (mprGetBufSpace(content) < HTTP_BUFSIZE) {
            mprGrowBuf(content, HTTP_BUFSIZE);
        }
    }
    *size = mprGetBufSpace(packet->content);
    mprAssert(*size > 0);
    return packet;
}
