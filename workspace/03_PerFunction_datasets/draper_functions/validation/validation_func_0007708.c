close()
{
    if (!closed)
    {
        if (outbufptr && blocked) set_blocked(false);
        if (sockfd) ::close(sockfd);

        delete[] buf;
        delete[] outbuf;
        closed = true;
    }
}
