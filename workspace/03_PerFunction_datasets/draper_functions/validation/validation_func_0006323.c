do_client(client_t *clnt)
{
    char openssl_buf[2048];
    usleep(200000);


    if (strcmp(clnt->testname, "Session Reuse") == 0)
    {
        sprintf(openssl_buf, "echo \"hello client\" | sh ../.././kick_openssl s_client -tls1 "
            "-connect localhost:%d %s 2>&1 | grep \"Session-ID:\"",
            g_port, clnt->openssl_option);
    }
    else if (strstr(clnt->testname, "GNUTLS") == NULL)
    {
        sprintf(openssl_buf, "echo \"hello client\" | sh ../.././kick_openssl s_client -tls1 "
#ifdef WIN32
            "-connect localhost:%d -quiet %s",
#else
            "-connect localhost:%d -quiet %s > /dev/null 2>&1",
#endif
        g_port, clnt->openssl_option);
    }
    else
    {
        sprintf(openssl_buf, "echo \"hello client\" | gnutls-cli "
#ifdef WIN32
            "-p %d %s 127.0.0.1",
#else
            "-p %d %s 127.0.0.1 > /dev/null 2>&1",
#endif
        g_port, clnt->openssl_option);
    }

    safe_system(openssl_buf);
}
