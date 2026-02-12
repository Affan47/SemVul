void wsrep_sst_cancel(bool call_wsrep_cb) {
  if (mysql_mutex_lock(&LOCK_wsrep_sst)) abort();
  if (!sst_cancelled) {
    WSREP_INFO("Initiating SST cancellation");
    sst_cancelled = true;


    if (sst_process) {
      WSREP_INFO("Terminating SST process");
      sst_process->terminate();
      sst_process = NULL;
    }


    if (call_wsrep_cb && sst_awaiting_callback) {
      WSREP_INFO("Signalling cancellation of the SST request.");
      const wsrep::gtid state_id = wsrep::gtid::undefined();
      sst_awaiting_callback = false;
      Wsrep_server_state::instance().provider().sst_received(state_id,
                                                             -ECANCELED);
    }
  }
  mysql_mutex_unlock(&LOCK_wsrep_sst);
}
