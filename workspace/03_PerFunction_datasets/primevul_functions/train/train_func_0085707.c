const void *FastCGITransport::getMorePostData(size_t& size) {


  long maxWait = RuntimeOption::ConnectionTimeoutSeconds;
  if (maxWait <= 0) {
    maxWait = 50;
  }

  Lock lock(this);
  while (m_bodyQueue.empty() && !m_bodyComplete) {
    wait(maxWait);
  }


  size = 0;
  if (!m_bodyQueue.empty()) {

    m_firstBody = !(m_firstBody && m_currBody);
    m_currBody = m_bodyQueue.pop_front();

    CHECK(m_currBody && m_currBody->length() > 0);
    size = m_currBody->length();
    return m_currBody->data();
  }

  return nullptr;
}
