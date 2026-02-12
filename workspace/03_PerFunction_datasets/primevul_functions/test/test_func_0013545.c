void closedata(void)
{
    volatile int tmp_xferfd = xferfd;

#ifdef WITH_TLS
    tls_close_session(&tls_data_cnx);
    tls_data_cnx = NULL;
#endif
    xferfd = -1;
    (void) close(tmp_xferfd);
}
