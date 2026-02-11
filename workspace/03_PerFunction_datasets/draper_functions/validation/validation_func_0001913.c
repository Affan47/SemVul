Create(
    AsyncSocket* socket,
    const SocketAddress& bind_address,
    const SocketAddress& remote_address) {
  scoped_ptr<AsyncSocket> owned_socket(socket);
  if (socket->Bind(bind_address) < 0) {
    LOG(LS_ERROR) << "Bind() failed with error " << socket->GetError();
    return NULL;
  }
  if (socket->Connect(remote_address) < 0) {
    LOG(LS_ERROR) << "Connect() failed with error " << socket->GetError();
    return NULL;
  }
  return new AsyncTCPSocket(owned_socket.release(), false);
}
