int wsrep_sst_donate(const std::string &msg, const wsrep::gtid &current_gtid,
                     const bool bypass) {


  local_status.set(wsrep::server_state::s_donor);

  if (!is_sst_request_valid(msg)) {
    std::ostringstream ss;
    std::for_each(std::begin(msg), std::end(msg), [&ss](char ch) {
      if (ch != 0)
        ss << ch;
      else
        ss << "<nullptr>";
    });
    WSREP_ERROR("Invalid sst_request: %s", ss.str().c_str());
    return WSREP_CB_FAILURE;
  }

  const char *method = msg.data();
  size_t method_len = strlen(method);
  const char *data = method + method_len + 1;

  wsp::env env(NULL);
  if (env.error()) {
    WSREP_ERROR("wsrep_sst_donate_cb(): env var ctor failed: %d", -env.error());
    return WSREP_CB_FAILURE;
  }

#if 0


  while (!wsrep_is_SE_initialized()) {
    sleep(1);
    THD *applier_thd = static_cast<THD *>(recv_ctx);
    if (applier_thd->killed == THD::KILL_CONNECTION) return WSREP_CB_FAILURE;
  }
#endif

  int ret;
  ret = sst_donate_other(method, data, current_gtid, bypass, env());

  return (ret >= 0 ? WSREP_CB_SUCCESS : WSREP_CB_FAILURE);
}
