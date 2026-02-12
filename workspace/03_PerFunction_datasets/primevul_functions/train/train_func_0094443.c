SSLNetVConnection::sslServerHandShakeEvent(int &err)
{

  if (sslHandshakeHookState == HANDSHAKE_HOOKS_CERT_INVOKE || sslHandshakeHookState == HANDSHAKE_HOOKS_CLIENT_CERT_INVOKE ||
      sslHandshakeHookState == HANDSHAKE_HOOKS_PRE_INVOKE) {
    return SSL_WAIT_FOR_HOOK;
  }


  if (sslHandshakeHookState == HANDSHAKE_HOOKS_PRE) {
    if (!curHook) {
      Debug("ssl", "Initialize preaccept curHook from NULL");
      curHook = ssl_hooks->get(TS_VCONN_START_INTERNAL_HOOK);
    } else {
      curHook = curHook->next();
    }

    if (nullptr == curHook) {
      sslHandshakeHookState = HANDSHAKE_HOOKS_SNI;
    } else {
      sslHandshakeHookState = HANDSHAKE_HOOKS_PRE_INVOKE;
      ContWrapper::wrap(nh->mutex.get(), curHook->m_cont, TS_EVENT_VCONN_START, this);
      return SSL_WAIT_FOR_HOOK;
    }
  }


  if (SSL_HOOK_OP_TUNNEL == hookOpRequested && !SNIMapping) {
    this->attributes = HttpProxyPort::TRANSPORT_BLIND_TUNNEL;
    SSL_free(this->ssl);
    this->ssl = nullptr;


    return EVENT_DONE;
  } else if (SSL_HOOK_OP_TERMINATE == hookOpRequested) {
    sslHandShakeComplete = true;
    return EVENT_DONE;
  }

  Debug("ssl", "Go on with the handshake state=%d", sslHandshakeHookState);


  if (this->handShakeReader) {
    if (BIO_eof(SSL_get_rbio(this->ssl))) {

      if (!this->handShakeReader->is_read_avail_more_than(0) && !this->handShakeHolder->is_read_avail_more_than(0)) {
        Debug("ssl", "%p first read\n", this);


        int retval = this->read_raw_data();
        if (retval < 0) {
          if (retval == -EAGAIN) {

            SSLVCDebug(this, "SSL handshake: EAGAIN");
            return SSL_HANDSHAKE_WANT_READ;
          } else {

            SSLVCDebug(this, "SSL handshake error: read_retval=%d", retval);
            return EVENT_ERROR;
          }
        } else if (retval == 0) {

          SSLVCDebug(this, "SSL handshake error: EOF");
          return EVENT_ERROR;
        }
      } else {
        update_rbio(false);
      }
    }
  }

#if TS_USE_TLS_ASYNC
  if (SSLConfigParams::async_handshake_enabled) {
    SSL_set_mode(ssl, SSL_MODE_ASYNC);
  }
#endif
  ssl_error_t ssl_error = SSLAccept(ssl);
#if TS_USE_TLS_ASYNC
  if (ssl_error == SSL_ERROR_WANT_ASYNC) {
    size_t numfds;
    OSSL_ASYNC_FD waitfd;

    if (SSL_get_all_async_fds(ssl, &waitfd, &numfds) && numfds > 0) {

      read_disable(nh, this);
      this->ep.stop();

      read.enabled = true;
      write_disable(nh, this);
      PollDescriptor *pd = get_PollDescriptor(this_ethread());
      this->ep.start(pd, waitfd, this, EVENTIO_READ);
      this->ep.type = EVENTIO_READWRITE_VC;
    }
  } else if (SSLConfigParams::async_handshake_enabled) {

    SSL_clear_mode(ssl, SSL_MODE_ASYNC);
    this->ep.stop();

    PollDescriptor *pd = get_PollDescriptor(this_ethread());
    this->ep.start(
      pd, this,
      EVENTIO_READ |
        EVENTIO_WRITE);
    if (ssl_error == SSL_ERROR_WANT_READ) {
      this->reenable(&read.vio);
      this->read.triggered = 1;
    }
  }
#endif
  bool trace = getSSLTrace();

  if (ssl_error != SSL_ERROR_NONE) {
    err = errno;
    SSLVCDebug(this, "SSL handshake error: %s (%d), errno=%d", SSLErrorName(ssl_error), ssl_error, err);


    char *buf = handShakeBuffer ? handShakeBuffer->buf() : nullptr;
    if (getTransparentPassThrough() && buf && *buf != SSL_OP_HANDSHAKE) {
      SSLVCDebug(this, "Data does not look like SSL handshake, starting blind tunnel");
      this->attributes     = HttpProxyPort::TRANSPORT_BLIND_TUNNEL;
      sslHandShakeComplete = false;
      return EVENT_CONT;
    }
  }

  switch (ssl_error) {
  case SSL_ERROR_NONE:
    if (is_debug_tag_set("ssl")) {
      X509 *cert = SSL_get_peer_certificate(ssl);

      Debug("ssl", "SSL server handshake completed successfully");
      if (cert) {
        debug_certificate_name("client certificate subject CN is", X509_get_subject_name(cert));
        debug_certificate_name("client certificate issuer CN is", X509_get_issuer_name(cert));
        X509_free(cert);
      }
    }

    sslHandShakeComplete = true;

    TraceIn(trace, get_remote_addr(), get_remote_port(), "SSL server handshake completed successfully");


    if (sslHandshakeBeginTime) {
      sslHandshakeEndTime                 = Thread::get_hrtime();
      const ink_hrtime ssl_handshake_time = sslHandshakeEndTime - sslHandshakeBeginTime;

      Debug("ssl", "ssl handshake time:%" PRId64, ssl_handshake_time);
      SSL_INCREMENT_DYN_STAT_EX(ssl_total_handshake_time_stat, ssl_handshake_time);
      SSL_INCREMENT_DYN_STAT(ssl_total_success_handshake_count_in_stat);
    }

    {
      const unsigned char *proto = nullptr;
      unsigned len               = 0;


#if TS_USE_TLS_ALPN
      SSL_get0_alpn_selected(ssl, &proto, &len);
#endif

#if TS_USE_TLS_NPN
      if (len == 0) {
        SSL_get0_next_proto_negotiated(ssl, &proto, &len);
      }
#endif

      if (len) {

        ink_assert(this->npnSet != nullptr);

        this->npnEndpoint = this->npnSet->findEndpoint(proto, len);
        this->npnSet      = nullptr;

        if (this->npnEndpoint == nullptr) {
          Error("failed to find registered SSL endpoint for '%.*s'", (int)len, (const char *)proto);
          return EVENT_ERROR;
        }

        Debug("ssl", "client selected next protocol '%.*s'", len, proto);
        TraceIn(trace, get_remote_addr(), get_remote_port(), "client selected next protocol'%.*s'", len, proto);
      } else {
        Debug("ssl", "client did not select a next protocol");
        TraceIn(trace, get_remote_addr(), get_remote_port(), "client did not select a next protocol");
      }
    }

    return EVENT_DONE;

  case SSL_ERROR_WANT_CONNECT:
    TraceIn(trace, get_remote_addr(), get_remote_port(), "SSL server handshake ERROR_WANT_CONNECT");
    return SSL_HANDSHAKE_WANT_CONNECT;

  case SSL_ERROR_WANT_WRITE:
    TraceIn(trace, get_remote_addr(), get_remote_port(), "SSL server handshake ERROR_WANT_WRITE");
    return SSL_HANDSHAKE_WANT_WRITE;

  case SSL_ERROR_WANT_READ:
    TraceIn(trace, get_remote_addr(), get_remote_port(), "SSL server handshake ERROR_WANT_READ");
    return SSL_HANDSHAKE_WANT_READ;


#ifdef SSL_ERROR_WANT_SNI_RESOLVE
  case SSL_ERROR_WANT_X509_LOOKUP:
    TraceIn(trace, get_remote_addr(), get_remote_port(), "SSL server handshake ERROR_WANT_X509_LOOKUP");
    return EVENT_CONT;
  case SSL_ERROR_WANT_SNI_RESOLVE:
    TraceIn(trace, get_remote_addr(), get_remote_port(), "SSL server handshake ERROR_WANT_SNI_RESOLVE");
#elif SSL_ERROR_WANT_X509_LOOKUP
  case SSL_ERROR_WANT_X509_LOOKUP:
    TraceIn(trace, get_remote_addr(), get_remote_port(), "SSL server handshake ERROR_WANT_X509_LOOKUP");
#endif
#if defined(SSL_ERROR_WANT_SNI_RESOLVE) || defined(SSL_ERROR_WANT_X509_LOOKUP)
    if (this->attributes == HttpProxyPort::TRANSPORT_BLIND_TUNNEL || SSL_HOOK_OP_TUNNEL == hookOpRequested) {
      this->attributes     = HttpProxyPort::TRANSPORT_BLIND_TUNNEL;
      sslHandShakeComplete = false;
      return EVENT_CONT;
    } else {

      return SSL_WAIT_FOR_HOOK;
    }
#endif

#if TS_USE_TLS_ASYNC
  case SSL_ERROR_WANT_ASYNC:
    TraceIn(trace, get_remote_addr(), get_remote_port(), "SSL server handshake ERROR_WANT_ASYNC");
    return SSL_WAIT_FOR_ASYNC;
#endif

  case SSL_ERROR_WANT_ACCEPT:
    TraceIn(trace, get_remote_addr(), get_remote_port(), "SSL server handshake ERROR_WANT_ACCEPT");
    return EVENT_CONT;

  case SSL_ERROR_SSL: {
    SSL_CLR_ERR_INCR_DYN_STAT(this, ssl_error_ssl, "SSLNetVConnection::sslServerHandShakeEvent, SSL_ERROR_SSL errno=%d", errno);
    char buf[512];
    unsigned long e = ERR_peek_last_error();
    ERR_error_string_n(e, buf, sizeof(buf));
    TraceIn(trace, get_remote_addr(), get_remote_port(),
            "SSL server handshake ERROR_SSL: sslErr=%d, ERR_get_error=%ld (%s) errno=%d", ssl_error, e, buf, errno);
    return EVENT_ERROR;
  }

  case SSL_ERROR_ZERO_RETURN:
    TraceIn(trace, get_remote_addr(), get_remote_port(), "SSL server handshake ERROR_ZERO_RETURN");
    return EVENT_ERROR;
  case SSL_ERROR_SYSCALL:
    TraceIn(trace, get_remote_addr(), get_remote_port(), "SSL server handshake ERROR_SYSCALL");
    return EVENT_ERROR;
  default:
    TraceIn(trace, get_remote_addr(), get_remote_port(), "SSL server handshake ERROR_OTHER");
    return EVENT_ERROR;
  }
}
