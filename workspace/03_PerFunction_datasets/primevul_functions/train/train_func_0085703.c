void FastCGITransport::onHeader(std::unique_ptr<folly::IOBuf> key_chain,
                                std::unique_ptr<folly::IOBuf> value_chain) {
  Cursor keyCur(key_chain.get());
  auto key = keyCur.readFixedString(key_chain->computeChainDataLength());


  if (strcasecmp(key.c_str(), "HTTP_PROXY") == 0) return;

  Cursor valCur(value_chain.get());
  auto value = valCur.readFixedString(value_chain->computeChainDataLength());

  m_requestParams[key] = value;
}
