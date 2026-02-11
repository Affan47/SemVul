SendResponse(SocketEvent evt)
{
    int len = 0;
    HttpBuffer* buf = pendingWrite_.GetFront();

    while (buf)
    {
        int sz = conn_->SendBuffer(buf->curPtr_, buf->curSize_);
        if (sz < 0) return -1;

        len += sz;
        if (sz < buf->curSize_)
        {
            buf->curPtr_ += sz;
            buf->curSize_ -= sz;
            break;
        }
        pendingWrite_.PopFront();
        writeBuffer_.ReleaseWriteBuffer(buf);
        buf = pendingWrite_.GetFront();
    }

    if (buf == NULL) FinishSendResponse();

    return len;
}
