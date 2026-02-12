CtPtr ProtocolV1::client_ready() {
  ldout(cct, 20) << __func__ << dendl;


  peer_global_seq = connect_reply.global_seq;
  connection->policy.lossy = connect_reply.flags & CEPH_MSG_CONNECT_LOSSY;

  once_ready = true;
  connect_seq += 1;
  ceph_assert(connect_seq == connect_reply.connect_seq);
  backoff = utime_t();
  connection->set_features((uint64_t)connect_reply.features &
                           (uint64_t)connection->policy.features_supported);
  ldout(cct, 10) << __func__ << " connect success " << connect_seq
                 << ", lossy = " << connection->policy.lossy << ", features "
                 << connection->get_features() << dendl;


  if (auth_meta->authorizer) {
    ldout(cct, 10) << __func__ << " setting up session_security with auth "
		   << auth_meta->authorizer.get() << dendl;
    session_security.reset(get_auth_session_handler(
        cct, auth_meta->authorizer->protocol,
	auth_meta->session_key,
        connection->get_features()));
  } else {


    ldout(cct, 10) << __func__ << " no authorizer, clearing session_security"
		   << dendl;
    session_security.reset();
  }

  if (connection->delay_state) {
    ceph_assert(connection->delay_state->ready());
  }
  connection->dispatch_queue->queue_connect(connection);
  messenger->ms_deliver_handle_fast_connect(connection);

  return ready();
}
