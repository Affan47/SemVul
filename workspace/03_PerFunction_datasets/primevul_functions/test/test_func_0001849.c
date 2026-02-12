int Socket::getLine(char *buff, int size, int timeout, bool honour_reloadconfig, bool *chopped, bool *truncated)
{
try {
    if (!isssl) {
        return BaseSocket::getLine(buff, size, timeout, honour_reloadconfig, chopped, truncated);
    }


    int i = 0;
    if ((bufflen - buffstart) > 0) {


        int tocopy = size - 1;
        if ((bufflen - buffstart) < tocopy)
            tocopy = bufflen - buffstart;
        char *result = (char *)memccpy(buff, buffer + buffstart, '\n', tocopy);
        if (result != NULL) {

            if (chopped)
                *chopped = true;
            *(--result) = '\0';
            buffstart += (result - buff) + 1;
            return result - buff;
        } else {
            i += tocopy;
            buffstart += tocopy;
        }
    }
    while (i < (size - 1)) {
        buffstart = 0;
        bufflen = 0;


            bufflen = SSL_read(ssl, buffer, 4096);
#ifdef NETDEBUG

#endif
        if (bufflen < 0) {


            std::cout << thread_id << "SSL_read failed with error " << SSL_get_error(ssl, bufflen) << std::endl;
            log_ssl_errors("ssl_read failed %s", "");
            return -1;

        }

        if (bufflen == 0) {
            buff[i] = '\0';
            if (truncated)
                *truncated = true;
            return i;
        }
        int tocopy = bufflen;
        if ((i + bufflen) > (size - 1))
            tocopy = (size - 1) - i;
        char *result = (char *)memccpy(buff + i, buffer, '\n', tocopy);
        if (result != NULL) {

            if (chopped)
                *chopped = true;
            *(--result) = '\0';
            buffstart += (result - (buff + i)) + 1;
            return i + (result - (buff + i));
        }
        i += tocopy;
    }

    buff[i] = '\0';
    if (truncated)
        *truncated = true;
    return i;
    } catch (...) {
    return -1;    }
}
