clientNegotiateSSL(int fd, void *data)
{
    ConnStateData *conn = (ConnStateData *)data;

    const int ret = tlsAttemptHandshake(conn, clientNegotiateSSL);
    if (ret <= 0) {
        if (ret < 0)
            conn->clientConnection->close();
        return;
    }

    Security::SessionPointer session(fd_table[fd].ssl);

#if USE_OPENSSL
    if (Security::SessionIsResumed(session)) {
        debugs(83, 2, "Session " << SSL_get_session(session.get()) <<
               " reused on FD " << fd << " (" << fd_table[fd].ipaddr <<
               ":" << (int)fd_table[fd].remote_port << ")");
    } else {
        if (Debug::Enabled(83, 4)) {


#if defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x00908000L
            PEM_ASN1_write(reinterpret_cast<i2d_of_void *>(i2d_SSL_SESSION),
                           PEM_STRING_SSL_SESSION, debug_log,
                           reinterpret_cast<char *>(SSL_get_session(session.get())),
                           nullptr, nullptr, 0, nullptr, nullptr);

#elif (ALLOW_ALWAYS_SSL_SESSION_DETAIL == 1)


            PEM_ASN1_write((int(*)())i2d_SSL_SESSION, PEM_STRING_SSL_SESSION,
                           debug_log,
                           reinterpret_cast<char *>(SSL_get_session(session.get())),
                           nullptr, nullptr, 0, nullptr, nullptr);


#else
            debugs(83, 4, "With " OPENSSL_VERSION_TEXT ", session details are available only defining ALLOW_ALWAYS_SSL_SESSION_DETAIL=1 in the source.");

#endif

        }

        debugs(83, 2, "New session " << SSL_get_session(session.get()) <<
               " on FD " << fd << " (" << fd_table[fd].ipaddr << ":" <<
               fd_table[fd].remote_port << ")");
    }
#else
    debugs(83, 2, "TLS session reuse not yet implemented.");
#endif


    conn->clientConnection->tlsNegotiations()->retrieveNegotiatedInfo(session);

#if USE_OPENSSL
    X509 *client_cert = SSL_get_peer_certificate(session.get());

    if (client_cert) {
        debugs(83, 3, "FD " << fd << " client certificate: subject: " <<
               X509_NAME_oneline(X509_get_subject_name(client_cert), 0, 0));

        debugs(83, 3, "FD " << fd << " client certificate: issuer: " <<
               X509_NAME_oneline(X509_get_issuer_name(client_cert), 0, 0));

        X509_free(client_cert);
    } else {
        debugs(83, 5, "FD " << fd << " has no client certificate.");
    }
#else
    debugs(83, 2, "Client certificate requesting not yet implemented.");
#endif

    conn->readSomeData();
}
