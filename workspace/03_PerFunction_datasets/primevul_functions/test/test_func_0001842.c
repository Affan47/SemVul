int Socket::readFromSocketn(char *buff, int len, unsigned int flags, int timeout)
{
    return readFromSocket(buff, len, flags, timeout, true, false);


#ifdef NODEF
    if (!isssl) {
        return BaseSocket::readFromSocketn(buff, len, flags, timeout);
    }

    int cnt, rc;
    cnt = len;


    if ((bufflen - buffstart) > 0) {
#ifdef NETDEBUG
        std::cout << thread_id << "Socket::readFromSocketn: data already in buffer; bufflen: " << bufflen << " buffstart: " << buffstart << std::endl;
#endif
        int tocopy = len;
        if ((bufflen - buffstart) < len)
            tocopy = bufflen - buffstart;
        memcpy(buff, buffer + buffstart, tocopy);
        cnt -= tocopy;
        buffstart += tocopy;
        buff += tocopy;
        if (cnt == 0)
            return len;
    }

    while (cnt > 0) {


        ERR_clear_error();
        rc = SSL_read(ssl, buff, cnt);
#ifdef NETDEBUG
        std::cout << thread_id << "ssl read said: " << rc << std::endl;
#endif

        if (rc < 0) {


            log_ssl_errors("ssl_read failed %s", "");
           s_errno = errno;
            return -1;
        }
        if (rc == 0) {
             ishup = true;
            return len - cnt;
        }
        buff += rc;
        cnt -= rc;
    }
    return len;
#endif
}
