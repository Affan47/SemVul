void wsrep_sst_received(THD *thd, const wsrep_uuid_t &uuid,
                        wsrep_seqno_t const seqno,
                        const void *const state __attribute__((unused)),
                        size_t const state_len __attribute__((unused))) {


  wsrep::gtid const sst_gtid(wsrep::id(uuid.data, sizeof(uuid.data)),
                             wsrep::seqno(seqno));

  if (!wsrep_before_SE()) {
    wsrep_set_SE_checkpoint(wsrep::gtid::undefined());
    wsrep_set_SE_checkpoint(sst_gtid);
  }
  wsrep_verify_SE_checkpoint(uuid, seqno);


  if (thd) {
    wsrep_store_threadvars(thd);
  }

  if (WSREP_ON) {
    int const rcode(seqno < 0 ? seqno : 0);
    wsrep_sst_complete(thd, rcode);
  }
}
