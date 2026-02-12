CtPtr ProtocolV1::server_ready() {
  ldout(cct, 20) << __func__ << " session_security is "
		 << session_security
		 << dendl;

  ldout(cct, 20) << __func__ << " accept done" << dendl;

  memset(&connect_msg, 0, sizeof(connect_msg));

  if (connection->delay_state) {
    ceph_assert(connection->delay_state->ready());
  }

  return ready();
}
