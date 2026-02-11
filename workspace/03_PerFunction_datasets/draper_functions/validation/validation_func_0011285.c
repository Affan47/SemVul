acquire_client(const URL& curl) {

    if(!curl) return NULL;
    if((curl.Protocol() != "http") &&
       (curl.Protocol() != "https") &&
       (curl.Protocol() != "httpg")) return NULL;
    ClientHTTP* client = NULL;
    std::string key = curl.ConnectionURL();
    clients_lock.lock();
    std::multimap<std::string,ClientHTTP*>::iterator cl = clients.find(key);
    if(cl != clients.end()) {
      client = cl->second;
      clients.erase(cl);
      clients_lock.unlock();
    } else {
      clients_lock.unlock();
      MCCConfig cfg;
      usercfg.ApplyToConfig(cfg);
      client = new ClientHTTP(cfg, curl, usercfg.Timeout());
    };
    return client;
  }
