bool FastCGIAcceptor::canAccept(const folly::SocketAddress& ) {

  auto const cons = m_server->getLibEventConnectionCount();
  return (RuntimeOption::ServerConnectionLimit == 0 ||
          cons < RuntimeOption::ServerConnectionLimit);
}
