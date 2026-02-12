void FastCGIServer::timeoutExpired() noexcept {


  if (m_acceptor) {
    m_acceptor->forceStop();
  }

  terminateServer();
}
