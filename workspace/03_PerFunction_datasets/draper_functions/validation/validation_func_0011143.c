acceptConnection()
{
  XmlRpcSocket::Socket s = XmlRpcSocket::accept(this->getfd());
  XmlRpcUtil::log(2, "XmlRpcServer::acceptConnection: socket %d", s);
  if (XmlRpcSocket::Invalid == s)
  {

    XmlRpcUtil::error("XmlRpcServer::acceptConnection: Could not accept connection (%s).", XmlRpcSocket::getErrorMsg().c_str());
  }
  else if ( ! XmlRpcSocket::setNonBlocking(s))
  {
    XmlRpcSocket::close(s);
    XmlRpcUtil::error("XmlRpcServer::acceptConnection: Could not set socket to non-blocking input mode (%s).", XmlRpcSocket::getErrorMsg().c_str());
  }
  else
  {
    XmlRpcUtil::log(2, "XmlRpcServer::acceptConnection: creating a connection");
    XmlRpcServerConnection* c = this->createConnection(s);
    if (c) this->dispatchConnection(c);
  }
}
