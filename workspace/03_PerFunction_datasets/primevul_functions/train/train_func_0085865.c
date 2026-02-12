void FastCGIServer::stop() {
  if (getStatus() != RunStatus::RUNNING) return;

  setStatus(RunStatus::STOPPING);
  HttpServer::MarkShutdownStat(ShutdownEvent::SHUTDOWN_DRAIN_READS);

  m_worker.getEventBase()->runInEventBaseThread([&] {


    m_socket->stopAccepting();

    if (RuntimeOption::ServerGracefulShutdownWait > 0) {


      if (m_acceptor) {
        m_acceptor->drainAllConnections();
      }

      std::chrono::seconds s(RuntimeOption::ServerGracefulShutdownWait);
      std::chrono::milliseconds m(s);
      scheduleTimeout(m);
    } else {


      if (m_acceptor) {
        m_acceptor->forceStop();
      }

      terminateServer();
    }
  });
}
