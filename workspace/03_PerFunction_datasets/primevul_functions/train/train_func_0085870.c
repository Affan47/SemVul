void FastCGIServer::onConnectionsDrained() {

  cancelTimeout();
  terminateServer();
}
