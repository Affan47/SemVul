void FastCGITransport::onSendEndImpl() {


  if (m_sendEnded) {
    return;
  }

  m_sendEnded = true;


  m_session->onComplete();
}
