int Socket::readFromSocket(char *buff, int len, unsigned int flags, int timeout, bool check_first, bool honour_reloadconfig)
{
    if (len == 0)
         return 0;
    if (!isssl) {
        return BaseSocket::readFromSocket(buff, len, flags, timeout, check_first, honour_reloadconfig);
    }


    int cnt = len;
    int tocopy = 0;
    if ((bufflen - buffstart) > 0) {
#ifdef NETDEBUG
        std::cout << thread_id << "Socket::readFromSocket: data already in buffer; bufflen: " << bufflen << " buffstart: " << buffstart << std::endl;
#endif
        tocopy = len;
        if ((bufflen - buffstart) < len)
            tocopy = bufflen - buffstart;
        memcpy(buff, buffer + buffstart, tocopy);
        cnt -= tocopy;
        buffstart += tocopy;
        buff += tocopy;
        if (cnt == 0)
            return len;
    }

    int rc;
    while (cnt > 0) {


        bool inbuffer;
        ERR_clear_error();
        if(true) {
            inbuffer = false;
           rc = SSL_read(ssl, buff, cnt);
        } else {
            inbuffer = true;
           rc = SSL_read(ssl, buffer, 4096);
        }

        if (rc < 0) {
            s_errno = errno;
            log_ssl_errors("ssl_read failed %s", "");
#ifdef NETDEBUG
        std::cout << thread_id << "ssl_read failed" << s_errno << " failed to read " << cnt << " bytes" << std::endl;
#endif
            rc = 0;
        }
        if (rc == 0) {
             ishup = true;
             return len - cnt;
             }

        if (inbuffer) {
#ifdef NETDEBUG
        std::cout << thread_id << "Inbuffer SSL read to return " << cnt << " bytes" << std::endl;
#endif

           buffstart = 0;
           bufflen = rc;
           if ((bufflen - buffstart) > 0) {
              tocopy = cnt;
              if ((bufflen - buffstart) < cnt)
              tocopy = bufflen - buffstart;
              memcpy(buff, buffer + buffstart, tocopy);
              cnt -= tocopy;
              buffstart += tocopy;
              buff += tocopy;
#ifdef NETDEBUG
        std::cout << thread_id << "Inbuffer SSL read to returned " << tocopy << " bytes" << std::endl;
#endif
           }
         } else {
        buff += rc;
        cnt -= rc;
         }

    }


      return len;
}
