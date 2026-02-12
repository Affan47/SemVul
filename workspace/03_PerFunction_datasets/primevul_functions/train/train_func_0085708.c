void FastCGITransport::onHeadersComplete() {
  m_scriptName   = getParamTyped<std::string>("SCRIPT_FILENAME");
  m_docRoot      = getParamTyped<std::string>("DOCUMENT_ROOT");
  m_pathTrans    = getParamTyped<std::string>("PATH_TRANSLATED");
  m_serverObject = getParamTyped<std::string>("SCRIPT_NAME");

  if (!m_docRoot.empty() && *m_docRoot.rbegin() != '/') {
    m_docRoot += '/';
  }

  if (m_scriptName.empty() || RuntimeOption::ServerFixPathInfo) {


    m_scriptName = getPathTranslated();
  }

  [&] {

    if (!strncmp(m_scriptName.c_str(), "proxy:", sizeof("proxy:") - 1)) {
      folly::StringPiece newName {m_scriptName};


      auto proxyPos = newName.find("://");
      if (proxyPos == std::string::npos) return;

      newName.advance(proxyPos + sizeof("://"));


      auto slashPos = newName.find('/');
      if (slashPos == std::string::npos) {
        m_scriptName.clear();
        return;
      }
      newName.advance(slashPos);


      auto questionPos = newName.find('?');
      if (questionPos != std::string::npos) {
        newName.subtract(newName.size() - questionPos);
      }

      m_scriptName = newName.str();
    }
  }();


  if (!m_scriptName.empty()) {
    if (m_scriptName.find(m_docRoot) == 0) {
      m_scriptName.erase(0, m_docRoot.length());
    } else {

      m_docRoot = "/";
    }
  }


  if (m_pathTrans.find(m_docRoot) == 0) {
    m_pathTrans.erase(0, m_docRoot.length());
  }

  auto qs = getParamTyped<std::string>("QUERY_STRING");
  if (!qs.empty()) {
    m_serverObject += "?";
    m_serverObject += qs;
  }


  auto const ex = getExtendedMethod();
  if (!strcmp(ex, "GET")) {
    m_method = Method::GET;
  } else if (!strcmp(ex, "HEAD")) {
    m_method = Method::HEAD;
  } else {
    m_method = Method::POST;
  }


  if (m_requestParams.count("HTTPS") && !m_requestParams["HTTPS"].empty() &&
      strcasecmp(m_requestParams["HTTPS"].c_str(), "OFF")) {
    setSSL();
  }
}
