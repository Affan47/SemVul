void FastCGIServer::waitForEnd() {


  m_worker.wait();
}
