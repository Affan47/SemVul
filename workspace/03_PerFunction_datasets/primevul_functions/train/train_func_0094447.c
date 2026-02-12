SSLNetVConnection::reenable(NetHandler *nh)
{
  Debug("ssl", "Handshake reenable from state=%d", sslHandshakeHookState);

  switch (sslHandshakeHookState) {
  case HANDSHAKE_HOOKS_PRE_INVOKE:
    sslHandshakeHookState = HANDSHAKE_HOOKS_PRE;
    break;
  case HANDSHAKE_HOOKS_CERT_INVOKE:
    sslHandshakeHookState = HANDSHAKE_HOOKS_CERT;
    break;
  default:
    break;
  }


  if (curHook != nullptr) {
    curHook = curHook->next();
    Debug("ssl", "iterate from reenable curHook=%p", curHook);
  }
  if (curHook != nullptr) {

    if (sslHandshakeHookState == HANDSHAKE_HOOKS_CLIENT_CERT) {
      sslHandshakeHookState = HANDSHAKE_HOOKS_CLIENT_CERT_INVOKE;
      curHook->invoke(TS_EVENT_SSL_VERIFY_CLIENT, this);
    } else if (sslHandshakeHookState == HANDSHAKE_HOOKS_CERT) {
      sslHandshakeHookState = HANDSHAKE_HOOKS_CERT_INVOKE;
      curHook->invoke(TS_EVENT_SSL_CERT, this);
    } else if (sslHandshakeHookState == HANDSHAKE_HOOKS_SNI) {
      curHook->invoke(TS_EVENT_SSL_SERVERNAME, this);
    } else if (sslHandshakeHookState == HANDSHAKE_HOOKS_PRE) {
      Debug("ssl", "Reenable preaccept");
      sslHandshakeHookState = HANDSHAKE_HOOKS_PRE_INVOKE;
      ContWrapper::wrap(nh->mutex.get(), curHook->m_cont, TS_EVENT_VCONN_START, this);
    }
    return;
  } else {

    switch (this->sslHandshakeHookState) {
    case HANDSHAKE_HOOKS_PRE:
    case HANDSHAKE_HOOKS_PRE_INVOKE:
      sslHandshakeHookState = HANDSHAKE_HOOKS_SNI;
      break;
    case HANDSHAKE_HOOKS_SNI:
      sslHandshakeHookState = HANDSHAKE_HOOKS_CERT;
      break;
    case HANDSHAKE_HOOKS_CERT:
    case HANDSHAKE_HOOKS_CERT_INVOKE:
      sslHandshakeHookState = HANDSHAKE_HOOKS_CLIENT_CERT;
      break;
    case HANDSHAKE_HOOKS_CLIENT_CERT:
    case HANDSHAKE_HOOKS_CLIENT_CERT_INVOKE:
      sslHandshakeHookState = HANDSHAKE_HOOKS_DONE;
      break;
    default:
      break;
    }
    Debug("ssl", "iterate from reenable curHook=%p %d", curHook, sslHandshakeHookState);
  }

  this->readReschedule(nh);
}
