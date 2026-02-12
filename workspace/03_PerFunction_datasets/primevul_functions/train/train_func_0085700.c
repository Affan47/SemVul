const void *FastCGITransport::getPostData(size_t& size) {


  if (m_firstBody) {
    CHECK(m_currBody);
    size = m_currBody->length();
    return m_currBody->data();
  }
  return getMorePostData(size);
}
