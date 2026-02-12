HHVM_METHOD(Memcache, addserver, const String& host, int port ,
            bool  , int weight ,
            int  , int  ,
            bool  ,
            const Variant&  ,
            int  ) {
  auto data = Native::data<MemcacheData>(this_);
  memcached_return_t ret;

  if (!host.empty() &&
      !strncmp(host.c_str(), "unix://", sizeof("unix://") - 1)) {
    const char *socket_path = host.substr(sizeof("unix://") - 1).c_str();
    ret = memcached_server_add_unix_socket_with_weight(&data->m_memcache,
                                                       socket_path, weight);
  } else {
    ret = memcached_server_add_with_weight(&data->m_memcache, host.c_str(),
                                           port, weight);
  }

  if (ret == MEMCACHED_SUCCESS) {
    return true;
  }

  return false;
}
