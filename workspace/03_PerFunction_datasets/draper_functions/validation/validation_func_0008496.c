start() {
    _assert_(true);
    std::string addr;
    if (!host_.empty()) {
      addr = kt::Socket::get_host_address(host_);
      if (addr.empty()) {
        serv_.log(kt::ThreadedServer::Logger::ERROR, "unknown host: %s", host_.c_str());
        return false;
      }
    }
    std::string nexpr;
    kc::strprintf(&nexpr, "%s:%d", addr.c_str(), port_);
    serv_.set_network(nexpr, tout_);
    worker_ = new Worker(this, thnum_);
    serv_.set_worker(worker_, thnum_);
    return serv_.start();
  }
